
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

GLint attributeCoord2d;

class SdlApplication {
public:

  SdlApplication() {
  }

  bool init_resources(void) {
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
    mProgram = std::make_unique<gst::Program>(
      std::vector<gst::Shader>({ vertexShader, fragmentShader }));
    if (!mProgram->link()) {
        std::cerr << "Failed to link program." << std::endl;
        return false;
    }

    // Bind the vertex array to the program.
    const char * attributeName = "coord2d";
    attributeCoord2d = glGetAttribLocation(mProgram->objectId(), attributeName);
    if (attributeCoord2d == -1) {
        std::cerr << "Could not bind attribute " << attributeName << std::endl;
        return false;
    }

    // Compiling, linking, and binding were successful.
    return true;
  }

  void render(SDL_Window* window) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(mProgram->objectId());
    glEnableVertexAttribArray(attributeCoord2d);
    GLfloat vertices[] = {
        0.0, 0.8,
        -0.8, -0.8,
        0.8, -0.8
    };
    glVertexAttribPointer(
        attributeCoord2d,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        vertices
    );

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(attributeCoord2d);

    SDL_GL_SwapWindow(window);
  }

  void free_resources() {
    mProgram->freeResources();
  }

  void mainLoop(SDL_Window* window) {
    while (true) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT)
                return;
        }
        render(window);
    }
  }

  int run(int argc, char * argv[]) {
    /* SDL-related initialising functions */
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("My First Triangle",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          640, 480,
                                          SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window);

    /* Extension wrangler initialising */
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {


        std::cerr << "Error: glewInit: " << glewGetErrorString(glew_status) << std::endl;
        return EXIT_FAILURE;
    }

    /* When all init functions run without errors,
         the program can initialise the resources */
    if (!init_resources())
        return EXIT_FAILURE;

    /* We can display something if everything goes OK */
    mainLoop(window);

    /* If the program exits in the usual way,
         free resources and exit with a success */
    free_resources();
    return EXIT_SUCCESS;
  }

private:
  std::unique_ptr<gst::Program> mProgram;
};

int main(int argc, char* argv[]) {
  SdlApplication app;
  return app.run(argc, argv);
}
