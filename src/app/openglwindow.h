#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QDebug>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QVector>

namespace s21 {

struct Color {
  float r;
  float g;
  float b;
  float a;
};

class OpenGLWindow : public QOpenGLWidget, protected QOpenGLFunctions_4_3_Core {
  Q_OBJECT
 public:
  OpenGLWindow(QWidget *parent = nullptr);
  ~OpenGLWindow();
  void initBuffer(const QString &nameFile);

 public:
  bool ortogonalP = false;
  bool perspectivP = true;
  float zoomLevel = 1.0f;
  Color foneColor{0.0f, 0.0f, 0.0f, 1.0f};
  QVector3D vertexColor{0.0f, 1.0f, 0.0f};
  QVector3D ribsColor{1.0f, 0.0f, 0.0f};
  float positionX = 0.0f;
  float positionY = 0.0f;
  float positionZ = -5.0f;
  float gapSize = 0.0f;
  float pointSize = 4.0f;
  int countVertex = 0;

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initShaders();

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

 private:
  QOpenGLShaderProgram mProgram;
  QOpenGLBuffer mArrayBuffer;
  QOpenGLBuffer mIndexBuffer;
  QMatrix4x4 mModelViewMatrix;
  QMatrix4x4 mProjectionMatrixPerspect;
  QMatrix4x4 mProjectionMatrixOrtogon;
  QVector2D mMousePosition;
  QQuaternion mRotation;
};
}  // namespace s21
#endif  // OPENGLWINDOW_H
