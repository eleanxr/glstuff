#include <qt/GLObjectView.h>

#include <QApplication>
#include <QMainWindow>

#include <iostream>

int main( int argc, char * argv[] )
{
  QApplication app( argc, argv );

  QMainWindow window;
  auto objectView = new qt::GLObjectView( &window );
  window.setCentralWidget( objectView );
  window.show();

  return app.exec();
}
