#include <qt/GLObjectView.h>

#include <osg/Camera>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Light>
#include <osg/Material>
#include <osg/ShapeDrawable>

#include <iostream>

namespace qt {

GLObjectView::GLObjectView( QWidget * parent ):
  QOpenGLWidget( parent ),
  mGraphicsWindow( new osgViewer::GraphicsWindowEmbedded( x(), y(), width(), height() ) ),
  mViewer( new osgViewer::Viewer )
{

}

GLObjectView::~GLObjectView()
{
}

void GLObjectView::initializeGL()
{
  osg::ref_ptr< osg::Group > root( new osg::Group );
  auto rootStateSet = root->getOrCreateStateSet();
  rootStateSet->setMode( GL_LIGHTING, osg::StateAttribute::ON );
  rootStateSet->setMode( GL_LIGHT0, osg::StateAttribute::ON );

  osg::ref_ptr< osg::Light > light( new osg::Light );
  light->setLightNum( 0 );
  light->setPosition( osg::Vec4f( 0.0f, 0.0f, 0.0f, 1.0f ) );
  light->setDiffuse( osg::Vec4f( 1.0f, 1.0f, 1.0f, 1.0f ) );
  light->setAmbient( osg::Vec4f( 1.0f, 1.0f, 1.0f, 1.0f ) );
  osg::ref_ptr< osg::LightSource > lightSource( new osg::LightSource );
  lightSource->setLight( light );
  lightSource->setLocalStateSetModes( osg::StateAttribute::ON );
  root->addChild( lightSource );

  osg::ref_ptr< osg::Cylinder > cylinder(
    new osg::Cylinder( osg::Vec3f( 0.0f, 0.0f, 0.0f ), 0.25f, 0.5f ) );
  osg::ref_ptr< osg::ShapeDrawable > drawable( new osg::ShapeDrawable( cylinder ) );
  drawable->setColor( osg::Vec4f( 1.0f, 0.0f, 1.0f, 1.0f ) );
  osg::ref_ptr< osg::Geode > geode( new osg::Geode );
  geode->addDrawable( drawable );
  lightSource->addChild( geode );

  auto stateSet = geode->getOrCreateStateSet();
  osg::ref_ptr< osg::Material > material( new osg::Material );
  material->setDiffuse( osg::Material::FRONT, osg::Vec4f( 1.0, 0.0, 0.0, 1.0 ) );
  stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
  stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

  osg::ref_ptr< osg::Camera > camera( new osg::Camera );
  camera->setViewport( 0, 0, width(), height() );
  camera->setClearColor( osg::Vec4f( 0.9f, 0.9f, 1.0f, 1.0f ) );
  auto aspectRatio = static_cast< float >( width() ) / static_cast< float >( height() );
  camera->setProjectionMatrixAsPerspective( 30.0, aspectRatio, 1.0f, 1000.0f );
  camera->setGraphicsContext( mGraphicsWindow );

  mViewer->setCamera( camera );
  mViewer->setSceneData( root );
  mViewer->setThreadingModel( osgViewer::Viewer::SingleThreaded );
  mViewer->realize();
}

void GLObjectView::paintGL()
{
  mViewer->frame();
}

} // namespace qt
