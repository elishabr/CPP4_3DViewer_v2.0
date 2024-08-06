#include "widget.h"

#include <QFileInfo>
#include <QGridLayout>

Widget::Widget(QWidget *parent) : QWidget(parent) {
  m_quickWidget = new QQuickWidget(this);
  // m_quickWidget->qmlRegisterSingletonInstance();
  m_quickWidget->setSource(QUrl("qrc:/TestApp/main.qml"));
  m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
  m_gridLayout = new QGridLayout(this);
  m_openGL = new s21::OpenGLWindow(this);
  m_gridLayout->addWidget(m_openGL, 0, 0);
  m_gridLayout->addWidget(m_quickWidget, 0, 1);
  QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  sizePolicy.setHorizontalStretch(1);
  m_openGL->setSizePolicy(sizePolicy);
  m_quickWidget->setFixedSize(100, this->maximumHeight());
  m_quickWidget->rootContext()->setContextProperty("AppControler", this);
}

Widget::~Widget() {}

int Widget::myIntProperty() const { return m_myIntProperty; }

void Widget::setMyIntProperty(int value) {
  if (m_myIntProperty != value) {
    m_myIntProperty = value;
    emit myIntPropertyChanged();
  }
}

QString Widget::nameFile() const { return m_nameFile; }

void Widget::setNameFile(QString nameF) {
  if (m_nameFile != nameF) {
    m_nameFile = nameF;
    emit nameFileChanged();
  }
}

void Widget::setFile(const QString &nameFile) {
  QFileInfo fileInfo(nameFile);
  setNameFile(fileInfo.fileName());
  m_openGL->initBuffer(nameFile);
  setMyIntProperty(m_openGL->countVertex);
  m_openGL->update();
  emit operationFile();
}

void Widget::setFoneColor(const QColor &color) {
  m_openGL->foneColor.r = color.red() / 255.0;
  m_openGL->foneColor.g = color.green() / 255.0;
  m_openGL->foneColor.b = color.blue() / 255.0;
  m_openGL->foneColor.a = 1.0f;
  m_openGL->update();
  emit operationFColor();
}

void Widget::setVertexColor(const QColor &color) {
  m_openGL->vertexColor.setX(color.red() / 255.0);
  m_openGL->vertexColor.setY(color.green() / 255.0);
  m_openGL->vertexColor.setZ(color.blue() / 255.0);
  m_openGL->update();
  emit operationVColor();
}

void Widget::setRibsColor(const QColor &color) {
  m_openGL->ribsColor.setX(color.red() / 255.0);
  m_openGL->ribsColor.setY(color.green() / 255.0);
  m_openGL->ribsColor.setZ(color.blue() / 255.0);
  m_openGL->update();
  emit operationVColor();
}

void Widget::setFigurSize(double size) {
  m_openGL->zoomLevel = size;
  m_openGL->update();
  emit operationFSize();
}

void Widget::setPositonX(double posX) {
  m_openGL->positionX = posX;
  m_openGL->update();
  emit operationPosX();
}

void Widget::setPositonY(double posY) {
  m_openGL->positionY = posY;
  m_openGL->update();
  emit operationPosY();
}

void Widget::setPositonZ(double posZ) {
  m_openGL->positionZ = posZ;
  m_openGL->update();
  emit operationPosZ();
}

void Widget::setGapSize(double gapS) {
  m_openGL->gapSize = gapS;
  m_openGL->update();
  emit operationGSize();
}

void Widget::setPointSize(double pointS) {
  m_openGL->pointSize = pointS;
  m_openGL->update();
  emit operationPSize();
}

void Widget::setProgection() {
  m_openGL->ortogonalP = !m_openGL->ortogonalP;
  m_openGL->perspectivP = !m_openGL->perspectivP;
  m_openGL->update();
  emit operationProg();
}
