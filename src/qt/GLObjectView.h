#ifndef GLOBJECTVIEW_H
#define GLOBJECTVIEW_H

#include <gst/Program.hpp>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

namespace qt {

class GLObjectView : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  GLObjectView( QWidget * parent = nullptr );
  virtual ~GLObjectView();

protected:

  virtual void initializeGL() override;
  virtual void paintGL() override;

private:

  GLint mAttributeCoord2d;
  GLuint mVboTriangle;
  gst::Program mProgram;

};

} // namespace qt

#endif // GLOBJECTVIEW_H
