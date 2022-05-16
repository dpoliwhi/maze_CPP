#include <QApplication>

#include "calculator.h"

int main(int argc, char *argv[]) {
  s21::model model;
  s21::controller cntr(&model);
  QApplication a(argc, argv);
  a.setWindowIcon(QIcon("./s21calc.icns"));
  s21::calculator w(&cntr);
  w.show();
  return a.exec();
}
