#include <qt/GLObjectView.h>

#include <QApplication>

#include <iostream>

int main( int argc, char * argv[] )
{
  QApplication app( argc, argv );

  QSurfaceFormat surfaceFormat;
  surfaceFormat.setDepthBufferSize( 24 );
  QSurfaceFormat::setDefaultFormat( surfaceFormat );

  qt::GLObjectView objectView;
  objectView.show();

  return app.exec();
}
