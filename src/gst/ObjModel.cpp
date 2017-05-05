#include <gst/ObjModel.h>

#include <fstream>

namespace gst {

ObjModel::ObjModel(
  const std::vector< VertexType >& vertices,
  const std::vector< ElementType >& elements,
  const std::vector< NormalType >& normals ):
  Model(),
  mVertices( vertices ),
  mElements( elements ),
  mNormals( normals )
{

}

ObjModel::ObjModel( ObjModel && rhs ):
  Model(),
  mVertices( std::move( rhs.mVertices ) ),
  mElements( std::move( rhs.mElements ) ),
  mNormals( std::move( rhs.mNormals ) )
{

}

ObjModel::~ObjModel()
{

}

const std::vector< Model::VertexType >& ObjModel::vertices() const
{
  return mVertices;
}

const std::vector< Model::ElementType >& ObjModel::elements() const
{
  return mElements;
}

const std::vector< Model::NormalType >& ObjModel::normals() const
{
  return mNormals;
}

ObjModel makeCubeModel()
{
  std::vector< Model::VertexType > vertices {
    // Front
    -1.0f, -1.0f, 1.0f, // 0
    1.0f, -1.0f, 1.0f,  // 1
    1.0f, 1.0f, 1.0f,   // 2
    -1.0f, 1.0f, 1.0f,  // 3
    // Back
    -1.0f, -1.0f, -1.0f,// 4
    1.0f, -1.0f, -1.0f, // 5
    1.0f, 1.0f, -1.0f,  // 6
    -1.0f, 1.0f, -1.0f, // 7
  };

  std::vector< Model::ElementType > elements {
    // front
    0, 1, 2,
    2, 3, 0,
    // top
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // bottom
    4, 0, 3,
    3, 7, 4,
    // left
    4, 5, 1,
    1, 0, 4,
    // right
    3, 2, 6,
    6, 7, 3,
  };

  std::vector< Model::NormalType > normals {

  };
  return ObjModel( vertices, elements, normals );
}

ObjModel loadObjModel( const boost::filesystem::path& filePath )
{
  std::ifstream in( filePath.string() );
}

} // namespace gst
