#ifndef gst_GLObject_hpp_
#define gst_GLObject_hpp_

#include <GL/glew.h>

namespace gst {

class GLObject {
public:

  GLObject(GLuint objectId);
  virtual ~GLObject();

  GLuint objectId() const;

private:
  const GLuint mObjectId;
};

} // namespace gst

#endif // gst_GLObject_hpp_
