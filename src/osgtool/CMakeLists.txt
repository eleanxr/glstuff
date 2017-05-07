cmake_minimum_required( VERSION 3.1 )

project( osgtool )

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

find_package( OpenSceneGraph REQUIRED COMPONENTS osgDB osgGA osgUtil osgViewer )
include_directories( ${OPENSCENEGRAPH_INCLUDE_DIRS} )

set( ${PROJECT_NAME}_HEADERS
  SceneBuilder.h
)

set( ${PROJECT_NAME}_SOURCES
  SceneBuilder.cpp
)

add_library( ${PROJECT_NAME}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${OPENSCENEGRAPH_LIBRARIES}
)
