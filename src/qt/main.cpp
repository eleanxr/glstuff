#include <qt/GLObjectView.h>

#include <QApplication>

#include <iostream>

int main( int argc, char * argv[] )
{
  QApplication app( argc, argv );

  qt::GLObjectView objectView;
  objectView.show();

  return app.exec();
}
