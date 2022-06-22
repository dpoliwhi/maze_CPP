#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), facadeMaze(nullptr), cell_width(0), cell_height(0) {}

void PaintWidget::paintMaze() {
  MP = {{-1, -1}, {-1, -1}, 0};
  pairData = facadeMaze->getData();
  rowsMaze = facadeMaze->getRowsAndCols().first;
  colsMaze = facadeMaze->getRowsAndCols().second;
  repaint();
}

void PaintWidget::generateMaze(size_t rows, size_t cols) {
  MP = {{-1, -1}, {-1, -1}, 0};
  facadeMaze->generate(rows, cols);
  pairData = facadeMaze->getData();
  rowsMaze = facadeMaze->getRowsAndCols().first;
  colsMaze = facadeMaze->getRowsAndCols().second;
  repaint();
}

void PaintWidget::mousePressEvent(QMouseEvent *event) {
  if (isOpen) {
    if (MP.press_count == 2 || MP.press_count == 0) {
      MP.mousePosition_end = {-1, -1};
      MP.mousePosition_start = {-1, -1};
      MP.press_count = 0;
      MP.mousePosition_start = QVector2D(event->pos());
      MP.press_count++;
    } else if (MP.press_count == 1) {
      MP.mousePosition_end = QVector2D(event->pos());
      MP.press_count++;
    }
    repaint();
  }
}

void PaintWidget::paintEvent(QPaintEvent *) {
  painter.begin(this);
  painter.setPen(QPen(QColor(32, 35, 42), 2));
  if (!isOpen) {
    painter.drawLine(1, 1, 500, 1);
    painter.drawLine(500, 1, 500, 500);
    painter.drawLine(500, 500, 1, 500);
    painter.drawLine(1, 500, 1, 1);
  } else {
    painter.drawLine(1, 1, 500, 1);
    painter.drawLine(1, 500, 1, 1);
    cell_width = 500.0 / colsMaze;
    cell_height = 500.0 / rowsMaze;
    float x = 0, y = 0;

    right_walls = pairData.first;
    bottom_walls = pairData.second;

    for (size_t i = 0; i < rowsMaze; i++) {
      for (size_t j = 0; j < colsMaze; j++) {
        x += cell_width;
        if (right_walls[i][j] == true) {
          painter.drawLine(x, y, x, y + cell_height);
        }
      }
      y += cell_height;
      x = 0;
    }
    x = 0, y = 0;
    for (size_t i = 0; i < rowsMaze; i++) {
      y += cell_height;
      for (size_t j = 0; j < colsMaze; j++) {
        if (bottom_walls[i][j] == true) {
          painter.drawLine(x, y, x + cell_width, y);
        }
        x += cell_width;
      }
      x = 0;
    }
    paintDot();
  }
  painter.end();
}

void PaintWidget::paintDot() {
  int size = (cell_width < cell_height ? cell_width : cell_height) / 2;
  painter.setPen(QPen(QColor(160, 29, 38), size));
  float x = 0, y = 0;
  int startx = -1, starty = -1, endx = -1, endy = -1;
  while (x < MP.mousePosition_start.x()) {
    x += cell_width;
    startx += 1;
  }
  while (y < MP.mousePosition_start.y()) {
    y += cell_height;
    starty += 1;
  }
  painter.drawPoint(x - (cell_width / 2), y - (cell_height / 2));
  x = 0, y = 0;
  while (x < MP.mousePosition_end.x()) {
    x += cell_width;
    endx += 1;
  }
  while (y < MP.mousePosition_end.y()) {
    y += cell_height;
    endy += 1;
  }
  painter.drawPoint(x - (cell_width / 2), y - (cell_height / 2));
  if (MP.press_count == 2) {
    path = facadeMaze->findPath(startx, starty, endx, endy);
    paintPath();
  }
}

void PaintWidget::paintPath() {
  painter.setPen(QPen(QColor(160, 29, 38), 2));
  int max = path.size() - 1;
  for (int i = 0; i < max; i++) {
    int startx = path[i].first * cell_width + (cell_width / 2);
    int starty = path[i].second * cell_height + (cell_height / 2);
    int endx = path[i + 1].first * cell_width + (cell_width / 2);
    int endy = path[i + 1].second * cell_height + (cell_height / 2);
    painter.drawLine(startx, starty, endx, endy);
  }
}
