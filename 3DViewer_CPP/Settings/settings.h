#pragma once

#include <QColor>
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include <iostream>

namespace s21 {

class Settings {
 private:
  QColor bgColor;
  QColor edgeColor;
  QColor vertexColor;
  double lineWidth;
  double pointSize;
  int lineType;
  int pointType;
  int projection;

 public:
  Settings();

  void setBGColor(QColor cl) { bgColor = cl; }
  QColor getBGColor() { return bgColor; }
  void setEdgeColor(QColor cl) { edgeColor = cl; }
  QColor getEdgeColor() { return edgeColor; }
  void setVertexColor(QColor cl) { vertexColor = cl; }
  QColor getVertexColor() { return vertexColor; }
  void setLineWidth(double width) { lineWidth = width; }
  double getLineWidth() { return lineWidth; }
  void setPointSize(double size) { pointSize = size; }
  double getPointSize() { return pointSize; }
  void setLineType(int type) { lineType = type; }
  int getLineType() { return lineType; }
  void setPointType(int type) { pointType = type; }
  int getPointType() { return pointType; }
  void setProjection(int type) { projection = type; }
  int getProjection() { return projection; }

  void getSettingFromFile();
  void setSettingToFile();
  void setDefaultSetting();
};

}  // namespace s21
