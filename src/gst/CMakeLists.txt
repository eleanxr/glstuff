project(gst)

find_package(Boost REQUIRED COMPONENTS
  system
  filesystem
)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
  ${Boost_INCLUDE_DIRS}
  ${OPENGL_INCLUDE_DIR}
  ${GLEW_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_HEADERS
  GLObject.hpp
  Shader.hpp
)

set(${PROJECT_NAME}_SOURCES
  GLObject.cpp
  Shader.cpp
)

add_library(${PROJECT_NAME}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
)
