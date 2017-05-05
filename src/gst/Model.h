#ifndef MODEL_H
#define MODEL_H

#include <vector>

namespace gst {

class Model
{
public:

  using VertexType = float;
  using ElementType = unsigned int;
  using NormalType = float;

  Model();
  virtual ~Model();

  virtual const std::vector< VertexType >& vertices() const = 0;
  virtual const std::vector< ElementType >& elements() const = 0;
  virtual const std::vector< NormalType >& normals() const = 0;
};

} // namespace gst

#endif // MODEL_H
