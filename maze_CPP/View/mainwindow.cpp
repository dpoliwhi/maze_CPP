#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(Facade *facadeInit, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), f(facadeInit) {
  ui->setupUi(this);
  ui->widget_maze->setFacade(facadeInit);
  ui->widget_cave->setFacade(facadeInit);
  connect(ui->pushButton_openfile, SIGNAL(released()), this, SLOT(openfilePressed()));
  connect(ui->pushButton_openfile_cave, SIGNAL(released()), this, SLOT(openfileCavePressed()));
  connect(ui->pushButton_generate, SIGNAL(released()), this, SLOT(generateMaze()));
  connect(ui->pushButton_savefile, SIGNAL(released()), this, SLOT(savefileMazePressed()));
  connect(ui->pushButton_nextstep, SIGNAL(released()), this, SLOT(nextStepPressed()));
  connect(ui->pushButton_generate_cave, SIGNAL(released()), this, SLOT(generateCavePressed()));
  connect(ui->pushButton_autostep, SIGNAL(released()), this, SLOT(autostepCavePressed()));
}

MainWindow::~MainWindow() {
  delete ui;
  delete timer;
}

void MainWindow::openfilePressed() {
  QString path;
  path = QFileDialog::getOpenFileName(this, "Open File", HOME_DIR "/Labyrinth", "*.txt");
  std::string filePath = path.toStdString();
  QFileInfo fileinfo(path);
  QString filename = fileinfo.fileName();
  ui->fileName->setText(filename);
  if (f->openFile(filePath)) {
    ui->widget_maze->isOpen = true;
    ui->widget_maze->paintMaze();

    std::pair<size_t, size_t> RowsAndCols = f->getRowsAndCols();
    int r = QString::number(RowsAndCols.first).toInt();
    ui->spinBox_rows->setValue(r);
    int c = QString::number(RowsAndCols.second).toInt();
    ui->spinBox_columns->setValue(c);
  } else {
    ui->widget_maze->isOpen = false;
    ui->spinBox_rows->setValue(0);
    ui->spinBox_columns->setValue(0);
    QMessageBox::information(NULL, QObject::tr("Информация"), "Please, open correct file!");
  }
}

void MainWindow::generateMaze() {
  f->cleanFileMaze();
  ui->widget_maze->isOpen = true;
  size_t rows = ui->spinBox_rows->text().toInt();
  size_t cols = ui->spinBox_columns->text().toInt();
  ui->widget_maze->generateMaze(rows, cols);
}

void MainWindow::openfileCavePressed() {
  if (timer != nullptr) timer->stop();
  QString path;
  path = QFileDialog::getOpenFileName(this, "Open File", HOME_DIR "/Caves", "*.txt");
  std::string filePath = path.toStdString();
  QFileInfo fileinfo(path);
  QString filename = fileinfo.fileName();
  ui->fileName_cave->setText(filename);
  if (f->openFileCave(filePath)) {
    ui->widget_cave->isOpen = true;
    ui->widget_cave->paintCave();
    std::pair<size_t, size_t> RowsAndCols = f->getRowsAndColsCave();
    int r = QString::number(RowsAndCols.first).toInt();
    ui->spinBox_caves_rows->setValue(r);
    int c = QString::number(RowsAndCols.second).toInt();
    ui->spinBox_caves_cols->setValue(c);
  } else {
    ui->widget_cave->isOpen = false;
    ui->spinBox_caves_rows->setValue(0);
    ui->spinBox_caves_cols->setValue(0);
    QMessageBox::information(NULL, QObject::tr("Информация"), "Please, open correct file!");
  }
}

void MainWindow::savefileMazePressed() {
  QString rows = ui->spinBox_rows->text();
  QString cols = ui->spinBox_columns->text();
  QString fileName = QFileDialog::getSaveFileName(
      this, "Save txt", HOME_DIR "Labyrinth/" + rows + "x" + cols + ".txt", "*.txt");
  QFile file(fileName);
  file.open(QIODevice::WriteOnly);
  file.close();
  f->saveFile(fileName.toStdString());
}

void MainWindow::generateCavePressed() {
  if (timer != nullptr) timer->stop();
  f->cleanFileCave();
  size_t rows = ui->spinBox_caves_rows->text().toInt();
  size_t cols = ui->spinBox_caves_cols->text().toInt();
  int chance = ui->spinBox_rand->text().toInt();
  ui->widget_cave->generateCave(rows, cols, chance);
}

void MainWindow::autostepCavePressed() {
  if (timer == nullptr) {
    timer = new QTimer;
  } else {
    timer->stop();
    timer = new QTimer;
  }
  size_t ms = ui->spinBox_auto->text().toInt();
  connect(timer, &QTimer::timeout, this, &MainWindow::onTimeOut);
  timer->start(ms);
}

void MainWindow::onTimeOut() {
  bool res = nextStepPressed();
  if (!res) timer->stop();
}

bool MainWindow::nextStepPressed() {
  size_t birth = ui->spinBox_birth->text().toInt();
  size_t death = ui->spinBox_death->text().toInt();
  bool res = ui->widget_cave->step(birth, death);
  if (!res) {
    QMessageBox::information(NULL, QObject::tr("Информация"), "Reached the final state of the cave!");
  }
  return res;
}

}  // namespace s21
