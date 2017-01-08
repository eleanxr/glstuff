#include <gst/Shader.hpp>

#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <utility>

namespace gst {

Shader::Shader(GLenum shaderType, const std::string& source)
: GLObject(glCreateShader(shaderType)),
  mShaderType(shaderType),
  mSource(source) {
}

Shader::~Shader() {
}

const std::string& Shader::source() const {
  return mSource;
}

Shader makeShader(
  GLenum shaderType,
  const boost::filesystem::path& sourceFile) {
  
  std::ifstream in(sourceFile.string());

  if (!in.good()) {
    throw std::runtime_error("Failed to read shader source file.");
  }

  std::ostringstream out;
  in.unsetf(std::ios::skipws);
  out.unsetf(std::ios::skipws);
  std::copy(
    std::istream_iterator<char>(in),
    std::istream_iterator<char>(),
    std::ostream_iterator<char>(out)
  );
  
  return std::move(Shader(shaderType, out.str()));
}

bool compile(const Shader& shader) {
    GLint compileOk = GL_FALSE;
    const char * source = shader.source().c_str();
    glShaderSource(shader.objectId(), 1, &source, NULL);
    glCompileShader(shader.objectId());
    glGetShaderiv(shader.objectId(), GL_COMPILE_STATUS, &compileOk);
    return compileOk;
}

} // namespace gst
