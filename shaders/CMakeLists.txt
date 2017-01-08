project(Shaders)

include(CopyFile)

set(${PROJECT_NAME}_FILES
  triangle_vertex_shader.glsl
  triangle_fragment_shader.glsl
)

foreach(_file ${${PROJECT_NAME}_FILES})
  copy_file(${_file})
endforeach()

