#pragma once

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QTimer>
#include <QVector>
#include <QWheelEvent>

#include "../Controller/facade.h"
#include "../Settings/settings.h"

class OpenGlWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit OpenGlWidget(QWidget *parent = nullptr);
  ~OpenGlWidget() {}

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 public:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

  void initShaders();
  void initObj(std::string fileName);

  // setters and getters:

  void setFacade(s21::Facade *facade) { f2 = facade; }
  void setSettings(s21::Settings *set) { settings = set; }
  void setScaleZ(float value) { scale_z = value; }
  float getScaleZ() { return scale_z; }
  void setMoveX(float value) { move_x = value; }
  float getMoveX() { return move_x; }
  void setMoveY(float value) { move_y = value; }
  float getMoveY() { return move_y; }
  void setQuaterion(QQuaternion updatedQuaterion) { rotation = updatedQuaterion; }
  QQuaternion getQuaterion() { return rotation; }

 private:
  s21::Facade *f2;
  s21::Settings *settings;

  QMatrix4x4 progectionMatrix;
  QOpenGLShaderProgram program;
  QQuaternion rotation;
  QOpenGLBuffer arrayBuffer;
  QOpenGLBuffer indexBuffer;
  QVector2D mousePosition;
  QVector2D mousePositionToMove;

  float scale_z = 0.0;
  float move_x = 0.0;
  float move_y = 0.0;
  bool move = false;
  double deltaExtremum = 0.0;

  struct VertexData {
    VertexData() {}
    explicit VertexData(QVector3D p) : position(p) {}
    QVector3D position;
  };
};
