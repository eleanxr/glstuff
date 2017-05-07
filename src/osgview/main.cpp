#include <iostream>

#include <osgtool/SceneBuilder.h>

#include <osgViewer/Viewer>

#include <osg/ArgumentParser>
#include <osg/GraphicsContext>

int main( int argc, char * argv[] )
{
  osg::ArgumentParser( &argc, argv );

  constexpr auto width = 800;
  constexpr auto height = 450;
  constexpr auto openglVersion = "4.5";

  osg::ref_ptr< osg::GraphicsContext::Traits > traits(
    new osg::GraphicsContext::Traits );
  traits->x = 0;
  traits->y = 0;
  traits->width = width;
  traits->height = height;
  traits->windowDecoration = true;
  traits->doubleBuffer = true;
  traits->glContextVersion = openglVersion;
  traits->readDISPLAY();

  osg::ref_ptr< osg::GraphicsContext > graphicsContext
    = osg::GraphicsContext::createGraphicsContext( traits );
  if ( !graphicsContext.valid() ) {
    std::cerr << "Failed to create OpenGL " << openglVersion << " context." << std::endl;
    return -1;
  }

  osgViewer::Viewer viewer;
  SceneBuilder builder;

  auto camera = builder.createCamera( width, height );
  auto sceneData = builder.createSceneRoot();

  camera->setGraphicsContext( graphicsContext );

  viewer.setCamera( camera );
  viewer.setSceneData( sceneData );

  graphicsContext->getState()->setUseModelViewAndProjectionUniforms( true );
  graphicsContext->getState()->setUseVertexAttributeAliasing( true );

  return viewer.run();
}
