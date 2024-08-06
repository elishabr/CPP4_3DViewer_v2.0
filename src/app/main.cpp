#include <QApplication>

#include "widget.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setWindowIcon(QIcon(":/my_app_icon_3DV.ico"));
  QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGL);
  // Создаем основное окно
  Widget window;
  window.setWindowTitle("Qt 3D Viewer");
  window.setStyleSheet("background-color: black;");
  window.resize(800, 600);

  // Показываем окно
  window.show();

  return app.exec();
}
