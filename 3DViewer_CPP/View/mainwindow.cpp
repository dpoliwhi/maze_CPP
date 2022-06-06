#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(Facade *facadeInit, Settings *setInit, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), f(facadeInit), settings(setInit) {
  ui->setupUi(this);
  ui->widget->setFacade(facadeInit);
  ui->widget->setSettings(setInit);
  settings->getSettingFromFile();
  setColorsAndTypesToSettings();
}

void MainWindow::on_pushButton_clicked() {
  QString path;
  path = QFileDialog::getOpenFileName(this, "Open File", HOME_DIR "/Objects/", "*.obj");
  std::string filePath = path.toStdString();
  ui->widget->initObj(filePath);
  ui->widget->setMoveX(0);
  ui->widget->setMoveY(0);
  QFileInfo fileinfo(path);
  QString filename = fileinfo.fileName();
  ui->label->setText(filename);
  std::pair<int, int> VertexesAndFaces = f->getRowsVertexesAndFaces();
  QString vertexes = QString::number(VertexesAndFaces.first);
  ui->lineEditVertices->setText(vertexes);
  QString edges = QString::number(VertexesAndFaces.second);
  ui->lineEditEdges->setText(edges);

  ui->widget->update();
}

float MainWindow::valueForTransformation(QString value) {
  std::string str = value.toStdString();
  float result = atof(str.c_str());
  return result;
}

void MainWindow::on_pushButtonTranslateX_clicked() {
  QString translate_x = ui->doubleSpinBoxTranslate->text();
  float translate = valueForTransformation(translate_x);
  float move_x = ui->widget->getMoveX();
  move_x += translate;
  ui->widget->setMoveX(move_x);
  ui->widget->update();
}

void MainWindow::on_pushButtonTranslateY_clicked() {
  QString translate_y = ui->doubleSpinBoxTranslate->text();
  float translate = valueForTransformation(translate_y);
  float move_y = ui->widget->getMoveY();
  move_y += translate;
  ui->widget->setMoveY(move_y);
  ui->widget->update();
}

void MainWindow::on_pushButtonRotateX_clicked() {
  QString rotate_x = ui->doubleSpinBoxRotate->text();
  float rotate = valueForTransformation(rotate_x);
  ui->widget->setQuaterion(QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), rotate) *
                           ui->widget->getQuaterion());
  ui->widget->update();
}

void MainWindow::on_pushButtonRotateY_clicked() {
  QString rotate_y = ui->doubleSpinBoxRotate->text();
  float rotate = valueForTransformation(rotate_y);
  ui->widget->setQuaterion(QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), rotate) *
                           ui->widget->getQuaterion());
  ui->widget->update();
}

void MainWindow::on_pushButtonRotateZ_clicked() {
  QString rotate_z = ui->doubleSpinBoxRotate->text();
  float rotate = valueForTransformation(rotate_z);
  ui->widget->setQuaterion(QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), rotate) *
                           ui->widget->getQuaterion());
  ui->widget->update();
}

void MainWindow::on_pushButtonPlus_clicked() {
  QString plus = ui->doubleSpinBoxScale->text();
  float res_plus = valueForTransformation(plus);
  float scale_z = ui->widget->getScaleZ();
  scale_z += res_plus;
  ui->widget->setScaleZ(scale_z);
  ui->widget->update();
}

void MainWindow::on_pushButtonMinus_clicked() {
  QString minus = ui->doubleSpinBoxScale->text();
  float res_plus = valueForTransformation(minus);
  float scale_z = ui->widget->getScaleZ();
  scale_z -= res_plus;
  ui->widget->setScaleZ(scale_z);
  ui->widget->update();
}

void MainWindow::on_chooseColor_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->label_color->setStyleSheet(
        "border: 1px solid #20232A; border-width: 2px; border-radius: 5px; background-color: #" +
        QString::number(color.rgb(), 16));
    settings->setEdgeColor(color);
    ui->widget->update();
  }
}

void MainWindow::on_chooseColorVert_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->label_color_2->setStyleSheet(
        "border: 1px solid #20232A; border-width: 2px; border-radius: 5px; background-color: #" +
        QString::number(color.rgb(), 16));
    settings->setVertexColor(color);
    ui->widget->update();
  }
}

void MainWindow::on_chooseColorBG_clicked() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->label_color_3->setStyleSheet(
        "border: 1px solid #20232A; border-width: 2px; border-radius: 5px; background-color: #" +
        QString::number(color.rgb(), 16));
    settings->setBGColor(color);
    ui->widget->update();
  }
}

void MainWindow::on_pushButtonScreen_clicked() {
  QPixmap screen = ui->widget->grab();
  QString screenFileName = QFileDialog::getSaveFileName(this, "Save image",
              HOME_DIR "Screenshots/screen.jpeg", "Images(* .bmp * .jpeg)");
  if (!screenFileName.isEmpty() && !screenFileName.isNull()) {
    screen.save(screenFileName);
  }
}

void MainWindow::on_doubleSpinBoxThicknessEdges_valueChanged(double arg1) {
  settings->setLineWidth(arg1);
  ui->widget->update();
}

void MainWindow::on_doubleSpinBoxThicknessEdges_2_valueChanged(double arg1) {
  settings->setPointSize(arg1);
  ui->widget->update();
}

void MainWindow::on_comboBox_currentIndexChanged(int index) {
  settings->setLineType(index);
  ui->widget->update();
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index) {
  settings->setPointType(index);
  ui->widget->update();
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index) {
  settings->setProjection(index);
  ui->widget->update();
}

void MainWindow::on_resetSettings_clicked() {
  settings->setDefaultSetting();
  setColorsAndTypesToSettings();
  ui->widget->update();
}

void MainWindow::closeEvent(QCloseEvent *) { settings->setSettingToFile(); }

void MainWindow::setColorsAndTypesToSettings() {
  ui->label_color_3->setStyleSheet(
      "border: 1px solid #20232A; border-width: 2px; border-radius: 5px; background-color: #" +
      QString::number(settings->getBGColor().rgb(), 16));
  ui->label_color->setStyleSheet(
      "border: 1px solid #20232A; border-width: 2px; border-radius: 5px; background-color: #" +
      QString::number(settings->getEdgeColor().rgb(), 16));
  ui->label_color_2->setStyleSheet(
      "border: 1px solid #20232A; border-width: 2px; border-radius: 5px; background-color: #" +
      QString::number(settings->getVertexColor().rgb(), 16));
  ui->comboBox->setCurrentIndex(settings->getLineType());
  ui->doubleSpinBoxThicknessEdges->setValue(settings->getLineWidth());
  ui->comboBox_2->setCurrentIndex(settings->getPointType());
  ui->doubleSpinBoxThicknessEdges_2->setValue(settings->getPointSize());
  ui->comboBox_3->setCurrentIndex(settings->getProjection());
}

void MainWindow::on_pushButtonGIF_clicked() {
  gifCount = 0;
  timer = new QTimer;
  connect(timer, &QTimer::timeout, this, &MainWindow::onTimeOut);
  timer->start(100);
  Gif = new QGifImage;
  Gif->setDefaultDelay(10);
}

void MainWindow::onTimeOut() {
  if (gifCount < 50) {
    QImage screen = ui->widget->grabFramebuffer();
    //        QImage screen2 = screen.scaled(640, 480, Qt::KeepAspectRatio);
    Gif->addFrame(screen);
    gifCount++;
  } else {
    timer->stop();
    QMessageBox::information(NULL, QObject::tr("Информация"),
                             "GIF file was successfully written\nNow you can save it");
    QString screenFileName =
        QFileDialog::getSaveFileName(this, "Save GIF", HOME_DIR "Gif/object.gif", "Images(* .gif)");
    Gif->save(screenFileName);
    gifCount = 0;
  }
}
}  // namespace s21
