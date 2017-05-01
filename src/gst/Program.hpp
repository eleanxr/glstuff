#ifndef gst_Program_hpp_
#define gst_Program_hpp_

#include <gst/GLObject.hpp>

#include <vector>

namespace gst {

class Shader;

class Program : public GLObject {
public:

  Program();
  virtual ~Program();

private:
};

bool link(
  const Program& program,
  const std::vector<Shader>& shaders);

} // namespace gst

#endif // gst_Program_hpp_
