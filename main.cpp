#include "View/mainwindow.h"
#include "Controller/facade.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    s21::Interface inter;
    s21::Facade one(&inter);
    s21::MainWindow w(&one);
    w.show();
    return a.exec();
}
