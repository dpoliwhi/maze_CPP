#pragma once

#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "../OpenGL/opengl_widget.h"
#include "../QtGifImage/src/gifimage/qgifimage.h"
#include "../Settings/settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Facade *facadeInit, Settings *setInit, QWidget *parent = nullptr);
  ~MainWindow() {}

 private slots:
  void on_pushButton_clicked();
  float valueForTransformation(QString value);
  void on_pushButtonTranslateX_clicked();
  void on_pushButtonTranslateY_clicked();
  void on_pushButtonRotateX_clicked();
  void on_pushButtonRotateY_clicked();
  void on_pushButtonRotateZ_clicked();
  void on_pushButtonPlus_clicked();
  void on_pushButtonMinus_clicked();
  void on_chooseColor_clicked();
  void on_chooseColorVert_clicked();
  void on_chooseColorBG_clicked();
  void on_pushButtonScreen_clicked();
  void on_doubleSpinBoxThicknessEdges_valueChanged(double arg1);
  void on_doubleSpinBoxThicknessEdges_2_valueChanged(double arg1);
  void on_comboBox_currentIndexChanged(int index);
  void on_comboBox_2_currentIndexChanged(int index);
  void on_resetSettings_clicked();
  void on_comboBox_3_currentIndexChanged(int index);
  void on_pushButtonGIF_clicked();

 public slots:
  void onTimeOut();

 private:
  Ui::MainWindow *ui;
  Facade *f;
  Settings *settings;

  virtual void closeEvent(QCloseEvent *);

  QTimer *timer;
  QGifImage *Gif;
  int gifCount;

  void setColorsAndTypesToSettings();
};
}  // namespace s21
