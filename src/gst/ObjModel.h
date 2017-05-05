#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <gst/Model.h>

#include <boost/filesystem/path.hpp>

namespace gst {

class ObjModel : public Model
{
public:
  ObjModel(
    const std::vector< VertexType >& vertices,
    const std::vector< ElementType >& elements,
    const std::vector< NormalType >& normals );
  ObjModel( ObjModel && rhs );
  virtual ~ObjModel();

  const std::vector< VertexType >& vertices() const;
  const std::vector< ElementType >& elements() const;
  const std::vector< NormalType >& normals() const;

private:
  const std::vector< VertexType > mVertices;
  const std::vector< ElementType > mElements;
  const std::vector< NormalType > mNormals;
};

ObjModel makeCubeModel();
ObjModel loadObjModel( const boost::filesystem::path& filePath );

} // namespace gst

#endif // OBJMODEL_H
