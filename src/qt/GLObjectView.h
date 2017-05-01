#ifndef GLOBJECTVIEW_H
#define GLOBJECTVIEW_H

#include <gst/Program.hpp>

#include <QOpenGLWidget>

#include <memory>

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

  GLint mAttributeCoord2d;
  GLuint mVboTriangle;
  std::unique_ptr< gst::Program > mProgram;

};

} // namespace qt

#endif // GLOBJECTVIEW_H
