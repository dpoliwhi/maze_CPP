#include "dialog_plot.h"

#include <QVector>
#include <QtMath>
#include <cmath>
#include <list>

#include "calculator.h"
#include "ui_dialog_plot.h"

namespace s21 {
Dialog_plot::Dialog_plot(controller *c, std::string in, QWidget *parent)
    : QDialog(parent), ui(new Ui::Dialog_plot), cntr(c), strin(in) {
  ui->setupUi(this);
  setFixedSize(size());
}

Dialog_plot::~Dialog_plot() {
  delete ui;
  delete cntr;
  strin.clear();
}

void Dialog_plot::on_pushButton_clicked() {
  QDialog::close();
  double ot_x = ui->ot_x->text().toDouble();
  double do_x = ui->do_x->text().toDouble();
  double ot_y = ui->ot_y->text().toDouble();
  double do_y = ui->do_y->text().toDouble();
  double div = fabs(do_x - ot_x);
  double step = div / 1000000;

  std::vector<double> x;
  std::vector<double> y;
  double x_i = ot_x;
  while (x_i < do_x) {
    x.push_back(x_i);
    x_i += step;
  }

  y = cntr->create_graph(strin, x);
  s21::Plot graph(ot_x, do_x, ot_y, do_y, x, y);
  graph.setModal(true);
  graph.exec();
}
}  // namespace s21
