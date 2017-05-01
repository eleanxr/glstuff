#include <qt/GLObjectView.h>

#include <gst/Shader.hpp>
#include <gst/GLObject.hpp>

#include <iostream>

namespace qt {

GLObjectView::GLObjectView( QWidget * parent ):
  QOpenGLWidget( parent ),
  mAttributeCoord2d(),
  mProgram()
{

}

GLObjectView::~GLObjectView()
{
}

void GLObjectView::initializeGL()
{
  glewInit();

  mProgram.reset( new gst::Program() );

  GLfloat vertices [] = {
    0.0, 0.8,
    -0.8, -0.8,
    0.8, -0.8
  };

  glGenBuffers( 1, &mVboTriangle );
  glBindBuffer( GL_ARRAY_BUFFER, mVboTriangle );
  glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

  // Create the vertex shader.
  gst::Shader vertexShader = gst::makeShader(
    GL_VERTEX_SHADER, "shaders/triangle_vertex_shader.glsl");
  if (!compile(vertexShader)) {
    std::cerr << "Failed to compile vertex shader" << std::endl;
  }

  // Create the fragment shader for the triangle.
  gst::Shader fragmentShader = gst::makeShader(
    GL_FRAGMENT_SHADER, "shaders/triangle_fragment_shader.glsl");
  if (!compile(fragmentShader)) {
    std::cerr << "Failed to compile fragment shader" << std::endl;
  }

  // Set up the shader program.
  auto shaders = std::vector<gst::Shader>({ vertexShader, fragmentShader});
  if (!link(*mProgram, shaders)) {
    std::cerr << "Failed to link program." << std::endl;
  }

  // Bind the vertex array to the program.
  const char * attributeName = "coord2d";
  mAttributeCoord2d = glGetAttribLocation( mProgram->objectId(), attributeName);
  if (mAttributeCoord2d == -1) {
    std::cerr << "Could not bind attribute " << attributeName << std::endl;
  }

}

void GLObjectView::paintGL()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glUseProgram(mProgram->objectId());
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

} // namespace qt
