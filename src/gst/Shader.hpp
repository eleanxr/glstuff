#ifndef gst_Shader_hpp_
#define gst_Shader_hpp_

#include <gst/GLObject.hpp>

#include <GL/glew.h>

#include <boost/filesystem.hpp>

namespace gst {

class Shader : public GLObject {
public:

  Shader(GLenum shaderType, const std::string& source);
  virtual ~Shader();

  const std::string& source() const;

private:
  const GLenum mShaderType;
  const std::string mSource;
};

Shader makeShader(
  GLenum shaderType,
  const boost::filesystem::path& sourceFile);

bool compile(const Shader& shader);

} // namespace gst

#endif // gst_Shader_hpp_
