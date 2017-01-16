
#include <gst/Program.hpp>
#include <gst/Shader.hpp>

#include <GL/glew.h>

#include <SDL.h>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Scene {
private:
  GLint mAttributeCoord2d;
  GLuint mVboTriangle;
  gst::Program mProgram;

public:

  Scene()
  : mAttributeCoord2d(),
    mProgram() {
  }
  
  virtual ~Scene() {
    glDeleteBuffers(1, &mVboTriangle);
  }

  bool initializeProgram() {
    GLfloat vertices[] = {
      0.0, 0.8,
      -0.8, -0.8,
      0.8, -0.8
    };
    glGenBuffers(1, &mVboTriangle);
    glBindBuffer(GL_ARRAY_BUFFER, mVboTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create the vertex shader.
    gst::Shader vertexShader = gst::makeShader(
      GL_VERTEX_SHADER, "shaders/triangle_vertex_shader.glsl");
    if (!compile(vertexShader)) {
      std::cerr << "Failed to compile vertex shader" << std::endl;
      return false;
    }

    // Create the fragment shader for the triangle.
    gst::Shader fragmentShader = gst::makeShader(
      GL_FRAGMENT_SHADER, "shaders/triangle_fragment_shader.glsl");
    if (!compile(fragmentShader)) {
      std::cerr << "Failed to compile fragment shader" << std::endl;
      return false;
    }

    // Set up the shader program.
    auto shaders = std::vector<gst::Shader>({ vertexShader, fragmentShader});
    if (!link(mProgram, shaders)) {
      std::cerr << "Failed to link program." << std::endl;
      return false;
    }

    // Bind the vertex array to the program.
    const char * attributeName = "coord2d";
    mAttributeCoord2d = glGetAttribLocation(mProgram.objectId(), attributeName);
    if (mAttributeCoord2d == -1) {
      std::cerr << "Could not bind attribute " << attributeName << std::endl;
      return false;
    }

    // Compiling, linking, and binding were successful.
    return true;
  }


  void render() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glUseProgram(mProgram.objectId());
    glBindBuffer(GL_ARRAY_BUFFER, mVboTriangle);
    glEnableVertexAttribArray(mAttributeCoord2d);
    glVertexAttribPointer(
      mAttributeCoord2d,
      2,
      GL_FLOAT,
      GL_FALSE,
      0,
      0
    );

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(mAttributeCoord2d);

  }
};

class SdlApplication {
private:
  SDL_Window * mWindow;

public:
  SdlApplication(int argc, char * argv[]) {
    initialize(argc, argv);
  }
  
  virtual ~SdlApplication() {
  }

  void mainLoop(Scene& scene) {
    while (true) {
      SDL_Event ev;
      while (SDL_PollEvent(&ev)) {
          if (ev.type == SDL_QUIT)
              return;
      }
      scene.render();
      SDL_GL_SwapWindow(mWindow);
    }
  }

  int initialize(int argc, char * argv[]) {
    /* SDL-related initialising functions */
    SDL_Init(SDL_INIT_VIDEO);
    mWindow = SDL_CreateWindow(
      "My First Triangle",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      640, 480,
      SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(mWindow);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);

    /* Extension wrangler initialising */
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {


        std::cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << std::endl;
        return EXIT_FAILURE;
    }
  }

  int run(Scene& scene) {
    /* When all init functions run without errors,
         the program can initialise the resources */
    if (!scene.initializeProgram())
        return EXIT_FAILURE;

    /* We can display something if everything goes OK */
    mainLoop(scene);

    /* If the program exits in the usual way,
         free resources and exit with a success */
    return EXIT_SUCCESS;
  }
};

int main(int argc, char* argv[]) {
  SdlApplication app(argc, argv);
  Scene scene;
  return app.run(scene);
}
