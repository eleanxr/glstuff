#ifndef gst_Program_hpp_
#define gst_Program_hpp_

#include <gst/GLObject.hpp>

#include <vector>

namespace gst {

class Shader;

class Program : public GLObject {
public:

  Program(const std::vector<Shader>& shaders);
  virtual ~Program();

  bool link();
  void freeResources();

private:
  std::vector<Shader> mShaders;
};

} // namespace gst

#endif // gst_Program_hpp_
