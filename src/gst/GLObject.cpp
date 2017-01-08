#include <gst/GLObject.hpp>

namespace gst {

GLObject::GLObject(GLuint objectId)
: mObjectId(objectId) {
}

GLObject::~GLObject() {
}

GLuint GLObject::objectId() const {
  return mObjectId;
}

} // namespace gst
