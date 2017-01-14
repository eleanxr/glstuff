#include <gst/Program.hpp>

#include <gst/Shader.hpp>

#include <GL/glew.h>

namespace gst {

Program::Program()
: GLObject(glCreateProgram()) {
}

Program::~Program() {
}

void Program::freeResources() {
  glDeleteProgram(objectId());
}

bool link(const Program& program, const std::vector<Shader>& shaders) {
  GLint linkOk = GL_FALSE;
  GLuint glObjectId = program.objectId();
  std::for_each(shaders.begin(), shaders.end(),
    [&glObjectId](const Shader& shader) {
      glAttachShader(glObjectId, shader.objectId());
    }
  );
  glLinkProgram(glObjectId);
  glGetProgramiv(glObjectId, GL_LINK_STATUS, &linkOk);
  return linkOk;
}

} // namespace gst
