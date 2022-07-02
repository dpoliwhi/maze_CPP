#pragma once

#include <QPainter>
#include <QWidget>

#include "../Controller/facade.h"

class PaintWidgetCave : public QWidget, protected QPainter {
  Q_OBJECT
 public:
  explicit PaintWidgetCave(QWidget *parent = nullptr);
  ~PaintWidgetCave() {}

  void setFacade(s21::Facade *facade) { facadeCave = facade; }
  void paintCave();
  bool step(size_t birth, size_t death);
  void generateCave(size_t rows, size_t cols, int chance);
  bool isOpen = false;

 protected:
  void paintEvent(QPaintEvent *) override;

 private:
  s21::Facade *facadeCave;
  QPainter painter;
  float cell_width;
  float cell_height;
  std::vector<std::vector<bool>> caveData;
  size_t rowsCave = 0;
  size_t colsCave = 0;
};
