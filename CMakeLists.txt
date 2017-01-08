cmake_minimum_required(VERSION 3.6)

project(SimpleOpenGL)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

add_subdirectory(shaders)

find_package(Boost REQUIRED COMPONENTS
  system
  filesystem
)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(
  ${Boost_INCLUDE_DIRS}
  ${SDL2_INCLUDE_DIR}
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
  triangle.cpp
)

add_executable(triangle
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(triangle
  ${Boost_LIBRARIES}
  ${SDL2_LIBRARY}
  ${OPENGL_LIBRARIES}
  ${GLEW_LIBRARIES}
)
