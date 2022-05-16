#include "substitute_x.h"

#include "calculator.h"
#include "ui_substitute_x.h"

namespace s21 {
Substitute_x::Substitute_x(controller *c, QWidget *parent)
    : QDialog(parent), ui(new Ui::Substitute_x), cntr(c) {
  ui->setupUi(this);
  setFixedSize(size());
}

Substitute_x::~Substitute_x() {
  delete ui;
  delete cntr;
  strin.clear();
}

void Substitute_x::on_calc_with_x_clicked() {
  if (ui->lineEdit->text().length()) {
    emit signalForm(ui->lineEdit->text());
    QDialog::close();
  }
}

void Substitute_x::on_creat_graph_clicked() {
  QDialog::close();
  dialog = new Dialog_plot(cntr, strin);
  dialog->exec();
}
}  // namespace s21
