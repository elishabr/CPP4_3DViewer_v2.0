#ifndef WIDGET_H
#define WIDGET_H

#include <QGridLayout>
#include <QObject>
#include <QQmlContext>
#include <QQuickWidget>

#include "openglwindow.h"

class Widget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(int myIntProperty READ myIntProperty WRITE setMyIntProperty NOTIFY
                 myIntPropertyChanged)
  Q_PROPERTY(
      QString nameFile READ nameFile WRITE setNameFile NOTIFY nameFileChanged)
 public:
  explicit Widget(QWidget* parent = 0);
  ~Widget();
  int myIntProperty() const;
  void setMyIntProperty(int value);
  QString nameFile() const;
  void setNameFile(QString nameF);
 public slots:
  void setFile(const QString& nameFile);
  void setFoneColor(const QColor& color);
  void setVertexColor(const QColor& color);
  void setRibsColor(const QColor& color);
  void setFigurSize(double size);
  void setPositonX(double posX);
  void setPositonY(double posY);
  void setPositonZ(double posZ);
  void setGapSize(double gapS);
  void setPointSize(double pointS);
  void setProgection();

 signals:
  void operationFile();
  void operationFColor();
  void operationVColor();
  void operationFSize();
  void operationPosX();
  void operationPosY();
  void operationPosZ();
  void operationProg();
  void operationRColor();
  void operationGSize();
  void operationPSize();
  void myIntPropertyChanged();
  void nameFileChanged();

 private:
  QQuickWidget* m_quickWidget;
  QGridLayout* m_gridLayout;
  s21::OpenGLWindow* m_openGL;
  int m_myIntProperty = 0;
  QString m_nameFile;
};

#endif  // WIDGET_H
