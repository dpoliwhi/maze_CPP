#include "opengl_widget.h"

OpenGlWidget::OpenGlWidget(QWidget *parent)
    : QOpenGLWidget(parent), indexBuffer(QOpenGLBuffer::IndexBuffer), f2(nullptr), settings(nullptr) {}

void OpenGlWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  initShaders();
}

void OpenGlWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  float aspect = w / (float)h;
  progectionMatrix.setToIdentity();
  progectionMatrix.perspective(45, aspect, 0.01, 10000.0);
}

void OpenGlWidget::paintGL() {
  QColor bgcolor = settings->getBGColor();
  glClearColor(bgcolor.redF(), bgcolor.greenF(), bgcolor.blueF(), bgcolor.alphaF());

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 MVPmatrix;
  MVPmatrix.setToIdentity();
  MVPmatrix.translate(move_x, move_y, scale_z);
  if (settings->getProjection() == 1) {
    MVPmatrix.ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 100.0f);
  }
  MVPmatrix.rotate(rotation);

  program.bind();
  program.setUniformValue("qt_ModelViewProjectionMatrix", progectionMatrix * MVPmatrix);

  arrayBuffer.bind();

  int vertLoc = program.attributeLocation("qt_Vertex");
  program.enableAttributeArray(vertLoc);
  program.setAttributeBuffer(vertLoc, GL_FLOAT, 0, 3, sizeof(VertexData));

  indexBuffer.bind();
  QColor edgecolor = settings->getEdgeColor();
  float edgesColor[4] = {edgecolor.redF(), edgecolor.greenF(), edgecolor.blueF(), edgecolor.alphaF()};
  program.setUniformValueArray(program.uniformLocation("color"), edgesColor, 1, 4);
  glLineWidth(settings->getLineWidth());
  int lineType = settings->getLineType();
  if (lineType == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00F0);
  } else if (lineType == 0) {
    glDisable(GL_LINE_STIPPLE);
  }
  glDrawElements(GL_LINES, f2->getCountVertexesAndFaces().second * 2, GL_UNSIGNED_INT, 0);

  int pointType = settings->getPointType();
  if (pointType != 0) {
    QColor vertexcolor = settings->getVertexColor();
    float vertexColor[4] = {vertexcolor.redF(), vertexcolor.greenF(), vertexcolor.blueF(),
                            vertexcolor.alphaF()};
    program.setUniformValueArray(program.uniformLocation("color"), vertexColor, 1, 4);
    glPointSize(settings->getPointSize());
    if (pointType == 1) {
      glDisable(GL_TRIANGLE_STRIP);
      glEnable(GL_POINT_SMOOTH);
    } else if (pointType == 2) {
      glDisable(GL_POINT_SMOOTH);
      glEnable(GL_TRIANGLE_STRIP);
    }
    glDrawArrays(GL_POINTS, 0, indexBuffer.size());
  }
}

void OpenGlWidget::mouseMoveEvent(QMouseEvent *event) {
  if (!move) {
    QVector2D delta = QVector2D(event->pos()) - mousePosition;
    mousePosition = QVector2D(event->pos());
    float angle = delta.length() / 2;
    QVector3D axis = QVector3D(delta.y(), delta.x(), 0.0);
    rotation = QQuaternion::fromAxisAndAngle(axis, angle) * rotation;
  } else {
    float delta_x, delta_y;
    delta_x = event->pos().x() - mousePositionToMove.x();
    delta_y = event->pos().y() - mousePositionToMove.y();
    move_x += delta_x / 1000;
    move_y += delta_y / -1000;
  }
  update();
}

void OpenGlWidget::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    mousePosition = QVector2D(event->pos());
    move = false;
  } else {
    mousePositionToMove = QVector2D(event->pos());
    move = true;
  }
  event->accept();
}

void OpenGlWidget::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    scale_z += deltaExtremum / 18;
  } else {
    scale_z -= deltaExtremum / 18;
  }
  update();
}

void OpenGlWidget::initShaders() {
  if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.vsh")) close();
  if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.fsh")) close();
  if (!program.link()) close();
}

void OpenGlWidget::initObj(std::string fileName) {
  QVector<VertexData> vertexes;
  QVector<GLuint> indexes;

  std::pair<std::vector<std::vector<double>>, std::vector<std::vector<int>>> pairObject;
  pairObject = f2->openFile(fileName);
  std::vector<std::vector<double>> V = pairObject.first;
  std::vector<std::vector<int>> F = pairObject.second;
  for (size_t i = 0; i < F.size(); i++) {
    for (size_t j = 0; j < F[i].size(); j++) {
      int oneCoord = F[i][j];
      vertexes.append(VertexData(QVector3D(V[oneCoord - 1][0], V[oneCoord - 1][1], V[oneCoord - 1][2])));
      indexes.append(static_cast<GLuint>(indexes.size()));
    }
  }
  if (vertexes.size()) {
    deltaExtremum = fabs(f2->getExtremum().second - f2->getExtremum().first);
    scale_z = -f2->getExtremum().second * 4;
  }

  arrayBuffer.create();
  arrayBuffer.bind();
  arrayBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof(VertexData));
  arrayBuffer.release();

  indexBuffer.create();
  indexBuffer.bind();
  indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof(GLuint));
  indexBuffer.release();
}
