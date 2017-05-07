#include <qt/GLObjectView.h>

#include <iostream>

namespace qt {

GLObjectView::GLObjectView( QWidget * parent ):
  QOpenGLWidget( parent ),
  mBuilder( new SceneBuilder() ),
  mGraphicsWindow( new osgViewer::GraphicsWindowEmbedded( x(), y(), width(), height() ) ),
  mViewer( new osgViewer::Viewer )
{

}

GLObjectView::~GLObjectView()
{
}

void GLObjectView::initializeGL()
{
  auto camera = mBuilder->createCamera( width(), height() );
  auto sceneRoot = mBuilder->createSceneRoot();

  camera->setGraphicsContext( mGraphicsWindow );
  mViewer->setCamera( camera );
  mViewer->setSceneData( sceneRoot );
  mViewer->setThreadingModel( osgViewer::Viewer::SingleThreaded );
  mViewer->realize();
}

void GLObjectView::paintGL()
{
  mViewer->frame();
}

} // namespace qt
