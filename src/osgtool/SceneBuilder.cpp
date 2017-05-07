#include "SceneBuilder.h"

#include <osgDB/ReadFile>

#include <osg/Camera>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/Program>
#include <osg/Shader>
#include <osg/ShapeDrawable>
#include <osg/StateSet>

namespace {

auto constexpr kVertexShaderSource =
  "#version 140 \n"
  " \n"
  "uniform mat4 osg_ModelViewProjectionMatrix; \n"
  "uniform mat3 osg_NormalMatrix; \n"
  "uniform vec3 ecLightDir; \n"
  " \n"
  "in vec4 osg_Vertex; \n"
  "in vec3 osg_Normal; \n"
  "out vec4 color; \n"
  " \n"
  "void main() \n"
  "{ \n"
  "    vec3 ecNormal = normalize( osg_NormalMatrix * osg_Normal ); \n"
  "    float diffuse = max( dot( ecLightDir, ecNormal ), 0. ); \n"
  "    color = vec4( vec3( diffuse ), 1. ); \n"
  " \n"
  "    gl_Position = osg_ModelViewProjectionMatrix * osg_Vertex; \n"
  "} \n";

auto constexpr kFragmentShaderSource =
  "#version 140 \n"
  " \n"
  "in vec4 color; \n"
  "out vec4 fragData; \n"
  " \n"
  "void main() \n"
  "{ \n"
  "    fragData = color; \n"
  "} \n";

} // namespace

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
  configureShaders( *rootStateSet );

  auto model = osgDB::readRefNodeFile( "/home/will/Documents/suzanne.obj" );
  root->addChild( model );

  auto stateSet = model->getOrCreateStateSet();
  osg::ref_ptr< osg::Material > material( new osg::Material );
  material->setDiffuse( osg::Material::FRONT, osg::Vec4f( 1.0, 0.0, 0.0, 1.0 ) );
  material->setEmission( osg::Material::FRONT, osg::Vec4f( 0.5f, 0.0f, 0.0f, 1.0f ) );
  stateSet->setAttributeAndModes( material, osg::StateAttribute::ON );
  stateSet->setMode( GL_DEPTH_TEST, osg::StateAttribute::ON );

  return root;
}

void SceneBuilder::configureShaders( osg::StateSet& stateset ) const
{
  osg::ref_ptr< osg::Shader > vertexShader(
    new osg::Shader( osg::Shader::VERTEX, kVertexShaderSource ) );
  osg::ref_ptr< osg::Shader > fragmentShader(
    new osg::Shader( osg::Shader::FRAGMENT, kFragmentShaderSource ) );
  osg::ref_ptr< osg::Program > program( new osg::Program );
  program->addShader( vertexShader );
  program->addShader( fragmentShader );
  stateset.setAttribute( program );

  osg::Vec3f lightDirection( 0.0f, 0.5f, 1.0f );
  lightDirection.normalize();
  stateset.addUniform( new osg::Uniform( "ecLightDir", lightDirection ) );
}
