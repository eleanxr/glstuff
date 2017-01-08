#include <gst/Program.hpp>

#include <gst/Shader.hpp>

#include <GL/glew.h>

namespace gst {

Program::Program(const std::vector<Shader>& shaders)
: GLObject(glCreateProgram()),
  mShaders(shaders) {
}

Program::~Program() {
}

bool Program::link() {
  GLint linkOk = GL_FALSE;
  GLuint glObjectId = objectId();
  std::for_each(mShaders.begin(), mShaders.end(),
    [&glObjectId](const Shader& shader) {
      glAttachShader(glObjectId, shader.objectId());
    }
  );
  glLinkProgram(glObjectId);
  glGetProgramiv(glObjectId, GL_LINK_STATUS, &linkOk);
  return linkOk;
}

void Program::freeResources() {
  glDeleteProgram(objectId());
}

} // namespace gst
