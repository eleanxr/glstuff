project(examples)

find_package(SDL2 REQUIRED)
include_directories(
  ${SDL2_INCLUDE_DIR}
)

add_executable(triangle triangle.cpp)
target_link_libraries(triangle
  ${SDL2_LIBRARY}
  gst
)
