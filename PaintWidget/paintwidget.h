#pragma once

#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QWidget>

#include "../Controller/facade.h"

class PaintWidget : public QWidget, protected QPainter {
  Q_OBJECT

 public:
  explicit PaintWidget(QWidget *parent = nullptr);
  ~PaintWidget() {}

  void setFacade(s21::Facade *facade) { facadeMaze = facade; }
  void paintMaze();
  void generateMaze(size_t rows, size_t cols);
  void mousePressEvent(QMouseEvent *event) override;
  void paintDot();
  void paintPath();
  bool isOpen = false;

 protected:
  void paintEvent(QPaintEvent *) override;

 private:
  s21::Facade *facadeMaze;
  std::pair<std::vector<std::vector<bool>>, std::vector<std::vector<bool>>> pairData;
  std::vector<std::vector<bool>> right_walls;
  std::vector<std::vector<bool>> bottom_walls;
  QPainter painter;
  struct mousePosition {
    QVector2D mousePosition_start;
    QVector2D mousePosition_end;
    size_t press_count = 0;
  };
  mousePosition MP;
  std::vector<std::pair<int, int>> path;
  float cell_width;
  float cell_height;
  size_t rowsMaze = 0;
  size_t colsMaze = 0;
};
