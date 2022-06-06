#include <QApplication>
#include "View/mainwindow.h"
#include "OpenGL/opengl_widget.h"
#include "Settings/settings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Interface inter;
    s21::Facade f(&inter);
    s21::Settings settings;
    s21::MainWindow w(&f, &settings);
    w.show();

  return a.exec();
}
