#include "plot.h"

#include <iostream>

#include "ui_plot.h"

namespace s21 {
Plot::Plot(QWidget *parent) : QDialog(parent), ui(new Ui::Plot) { ui->setupUi(this); }

Plot::Plot(int xaxis_ot, int xaxis_do, int yaxis_ot, int yaxis_do, std::vector<double> x,
           std::vector<double> y, QWidget *parent)
    : QDialog(parent), ui(new Ui::Plot) {
  ui->setupUi(this);
  ui->widget->xAxis->setRange(xaxis_ot, xaxis_do);
  ui->widget->yAxis->setRange(yaxis_ot, yaxis_do);

  QVector<double> xx = QVector<double>(x.begin(), x.end());
  QVector<double> yy = QVector<double>(y.begin(), y.end());

  ui->widget->addGraph();
  ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 1));
  ui->widget->graph(0)->addData(xx, yy);
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}

Plot::~Plot() { delete ui; }

}  // namespace s21
