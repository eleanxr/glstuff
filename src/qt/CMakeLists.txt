cmake_minimum_required( VERSION 3.1 )

project( ShaderLab )

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# FIXME: Don't rely on this
set( QT5_INSTALL_PATH "$ENV{HOME}/Qt/5.8/gcc_64" CACHE PATH "Qt5 Install Directory" )

list( APPEND CMAKE_PREFIX_PATH ${QT5_INSTALL_PATH} )

find_package( Qt5Core )
find_package( Qt5Widgets )
find_package( Qt5OpenGL )

set( ${PROJECT_NAME}_HEADERS
  GLObjectView.h
)

set( ${PROJECT_NAME}_SOURCES
  GLObjectView.cpp
  main.cpp
)

add_executable( ${PROJECT_NAME}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(
  ${PROJECT_NAME}
  Qt5::Core
  Qt5::Widgets
  gst
)
