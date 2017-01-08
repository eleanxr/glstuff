cmake_minimum_required(VERSION 3.6)

project(GLStuff)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(src)

add_subdirectory(src/gst)

add_subdirectory(shaders)
add_subdirectory(examples)

