#pragma once

#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>
#include <QTimer>

#include "../PaintWidget/paintwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(Facade* facadeInit, QWidget* parent = nullptr);
  ~MainWindow();

  void onTimeOut();

 private slots:
  void openfilePressed();
  void generateMaze();
  void openfileCavePressed();
  void savefileMazePressed();
  bool nextStepPressed();
  void generateCavePressed();
  void autostepCavePressed();

 private:
  Ui::MainWindow* ui;
  Facade* f;
  QTimer* timer;
};
}  // namespace s21
