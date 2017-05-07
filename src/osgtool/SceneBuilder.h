#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H

#include <osg/Camera>
#include <osg/Node>
#include <osg/ref_ptr>

class SceneBuilder
{
public:
  SceneBuilder();

  osg::ref_ptr< osg::Camera > createCamera( int viewportWidth, int viewportHeight ) const;
  osg::ref_ptr< osg::Node > createSceneRoot() const;

private:

  void configureShaders( osg::StateSet& stateset ) const;

};

#endif // SCENEBUILDER_H
