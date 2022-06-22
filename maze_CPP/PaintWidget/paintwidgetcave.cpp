#include "paintwidgetcave.h"

PaintWidgetCave::PaintWidgetCave(QWidget *parent)
    : QWidget(parent), facadeCave(nullptr), cell_width(0), cell_height(0) {}

void PaintWidgetCave::paintCave() {
  caveData = facadeCave->getDataCave();
  rowsCave = facadeCave->getRowsAndColsCave().first;
  colsCave = facadeCave->getRowsAndColsCave().second;
  repaint();
}

void PaintWidgetCave::paintEvent(QPaintEvent *) {
  painter.begin(this);
  painter.setPen(QPen(QColor(32, 35, 42), 2));
  painter.drawLine(1, 1, 500, 1);
  painter.drawLine(500, 1, 500, 500);
  painter.drawLine(500, 500, 1, 500);
  painter.drawLine(1, 500, 1, 1);
  if (isOpen) {
    cell_width = 500.0 / colsCave;
    cell_height = 500.0 / rowsCave;
    float x = 0, y = 0;
    QBrush brush(QColor(32, 35, 42));
    painter.setBrush(brush);
    for (size_t i = 0; i < rowsCave; i++) {
      for (size_t j = 0; j < colsCave; j++) {
        if (caveData[i][j] == true) {
          painter.drawRect(x, y, cell_width, cell_height);
        }
        x += cell_width;
      }
      y += cell_height;
      x = 0;
    }
  }
  painter.end();
}

bool PaintWidgetCave::step(size_t birth, size_t death) {
  bool res = facadeCave->caveStep(birth, death);
  caveData = facadeCave->getDataCave();
  repaint();
  return res;
}

void PaintWidgetCave::generateCave(size_t rows, size_t cols, int chance) {
  isOpen = facadeCave->generateCave(rows, cols, chance);
  caveData = facadeCave->getDataCave();
  rowsCave = rows;
  colsCave = cols;
  repaint();
}
