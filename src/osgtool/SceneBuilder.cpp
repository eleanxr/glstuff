#include "SceneBuilder.h"

#include <osgDB/ReadFile>

#include <osg/Camera>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/ShapeDrawable>

SceneBuilder::SceneBuilder()
{

}

osg::ref_ptr< osg::Camera > SceneBuilder::createCamera(
  int viewportWidth,
  int viewportHeight ) const
{
  osg::ref_ptr< osg::Camera > camera( new osg::Camera );
  camera->setViewport( 0, 0, viewportWidth, viewportHeight );
  camera->setClearColor( osg::Vec4f( 0.5f, 0.0f, 0.5f, 1.0f ) );
  auto aspectRatio
    = static_cast< float >( viewportWidth ) /
      static_cast< float >( viewportHeight );
  camera->setProjectionMatrixAsPerspective( 30.0, aspectRatio, 1.0f, 1000.0f );
  return camera;
}

osg::ref_ptr< osg::Node > SceneBuilder::createSceneRoot() const
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

  auto model = osgDB::readRefNodeFile( "/home/will/Documents/suzanne.obj" );
  lightSource->addChild( model );

  auto stateSet = model->getOrCreateStateSet();
  osg::ref_ptr< osg::Material > material( new osg::Material );
  material->setDiffuse( osg::Material::FRONT, osg::Vec4f( 1.0, 0.0, 0.0, 1.0 ) );
  material->setEmission( osg::Material::FRONT, osg::Vec4f( 0.5f, 0.0f, 0.0f, 1.0f ) );
  stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
  stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

  return root;
}
