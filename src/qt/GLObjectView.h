#ifndef GLOBJECTVIEW_H
#define GLOBJECTVIEW_H

#include <QOpenGLWidget>

#include <osg/ref_ptr>

#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>

namespace qt {

class GLObjectView : public QOpenGLWidget
{
  Q_OBJECT

public:
  GLObjectView( QWidget * parent = nullptr );
  virtual ~GLObjectView();

protected:

  virtual void initializeGL() override;
  virtual void paintGL() override;

private:

  osg::ref_ptr< osgViewer::Viewer > mViewer;
  osg::ref_ptr< osgViewer::GraphicsWindowEmbedded > mGraphicsWindow;

};

} // namespace qt

#endif // GLOBJECTVIEW_H
