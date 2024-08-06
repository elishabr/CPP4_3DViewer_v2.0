#include "openglwindow.h"

#include "fileparserfacade.h"

s21::OpenGLWindow::OpenGLWindow(QWidget *parent)
    : QOpenGLWidget(parent),
      mIndexBuffer(
          QOpenGLBuffer::IndexBuffer)  // явно указываем, что это индексный
                                       // буфер, по умолчанию он вершинный
{}

s21::OpenGLWindow::~OpenGLWindow() {
}  // возможно надо что-то отчищать я не тестировал на утечки памяти

void s21::OpenGLWindow::initializeGL() {
  initializeOpenGLFunctions();  // инициализация стандартных функция OpenGL_4_3
  glClearColor(
      0.0f, 0.0f, 0.0f,
      1.0f);  // выбор цвета отчистки поверхности OpenGL_4_3 (заливки фона)

  glEnable(GL_DEPTH_TEST);  // включает буфер глубины
  // glEnable(GL_CULL_FACE);

  initShaders();  // загрузка вершинного и фрагментного шейдера
  // initBuffer("C:\\Users\\Nikita\\Downloads\\Telegram Desktop\\skull
  // (2).obj"); // заполнения буверов VBA и IBO для хранения координат обьекта
}

void s21::OpenGLWindow::resizeGL(int w, int h) {
  // Calculate aspect ratio
  qreal aspect = qreal(w) / qreal(h ? h : 1);
  mProjectionMatrixPerspect
      .setToIdentity();  // создание еденичной матрицы проекции для
                         // перспективной проекции
  mProjectionMatrixOrtogon
      .setToIdentity();  // создание еденичной матрицы проекции для
                         // ортогональной проекции
  mProjectionMatrixPerspect.perspective(
      45.0f, aspect, 0.1f, 10.0f);  // задание матрици перспективной проекции
  mProjectionMatrixOrtogon.ortho(
      -(float)w / this->width(), (float)w / this->width(),
      -(float)h / this->width(), (float)h / this->width(), 0.1f, 10.0f);
  // задание матрици ортогональной проекции
}

void s21::OpenGLWindow::paintGL() {
  glClearColor(foneColor.r, foneColor.g, foneColor.b, foneColor.a);
  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT);  // отчистка буфера цвета и глубины

  glEnable(GL_PROGRAM_POINT_SIZE);  // включаем возможность изменять размер
                                    // вершин при отрисовке обьекта
  glPolygonMode(GL_FRONT_AND_BACK,
                GL_LINE);  // отвечает за отрисовку только граний
  glLineWidth(3.0f);  // отвечает за толщену граний

  mModelViewMatrix.setToIdentity();  // создание еденичной матрицы поворота
                                     // (модельновидовая матрица)
  mModelViewMatrix.translate(positionX, positionY,
                             positionZ);  // немного отдалили обьект, чтобы он
                                          // попадал облость видимости камеры
  mModelViewMatrix.rotate(
      mRotation);  // эта функция поворота в нее мы подаем обьект Кваторион,
                   // который хранит параметры поворота
  mModelViewMatrix.scale(zoomLevel);

  mProgram.bind();  // поолучаем доступ к нашей шейдерной программе созданной в
                    // initShaders()

  if (perspectivP)
    mProgram.setUniformValue("mvp_matrix",
                             mProjectionMatrixPerspect *
                                 mModelViewMatrix);  // перспективная проекция
  else if (ortogonalP)
    mProgram.setUniformValue(
        "mvp_matrix",
        mProjectionMatrixOrtogon * mModelViewMatrix);  // ортогональная проекция
  mProgram.setUniformValue("u_dashSize",
                           5.0f);  // параметры для шейдера размер пунктира
  mProgram.setUniformValue(
      "u_gapSize",
      gapSize);  // параметры для шейдера размер пробела между пунктирами
  mProgram.setUniformValue("u_pointSize", pointSize);  // изменяет размер вешины
  mProgram.setUniformValue("u_color", ribsColor);  // цвет ребер
  mProgram.setUniformValue("u_shape", 1);  // вершины не отрисовываются

  mArrayBuffer.bind();  // получаем доступ к VBO - вершиннному буферу
  mIndexBuffer.bind();  // получаем доступ к IBO - индексному буферу
  quintptr offset = 0;  // задаем пазицию с которой будет обрабатываться каждая
                        // вершина. B нашем случае в вершине содержится
  // QVector3D position затем QVector3D color, первое место в памяти начинается
  // с 0 значит для выбора QVector3D position нам надо указать offset = 0

  int vertexLocation = mProgram.attributeLocation(
      "a_position");  // берем индекс атрибута в шейдоре - это  layout(location
                      // = 0)
  if (vertexLocation == -1) {
    qWarning() << "Could not find attribute a_position";
  } else {
    mProgram.enableAttributeArray(
        vertexLocation);  // включаем массив атрибутов по этому индексу для
                          // шейдорной программы
    mProgram.setAttributeBuffer(
        vertexLocation, GL_FLOAT, offset, 3,
        sizeof(float) * 3);  //соидиняем наш активный буфер mArrayBuffer.bind()
                             //с шейдорной программой через полученный индекс
  }

  glDrawElements(GL_LINES, mIndexBuffer.size(), GL_UNSIGNED_INT,
                 0);  // рисуем триугольники используя VBO и IBO
  mProgram.setUniformValue("u_shape", 0);  // отрисовывка вершин
  mProgram.setUniformValue("u_color", vertexColor);  // цвет вершин
  if (true)
    glDrawElements(GL_POINTS, mIndexBuffer.size(), GL_UNSIGNED_INT,
                   0);  // условие на отрисовку вершин
}

void s21::OpenGLWindow::initShaders() {
  if (!mProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":/vshader.vsh")) {
    qWarning() << "Vertex shader error:" << mProgram.log();
    close();
  }
  if (!mProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":/fshader.fsh")) {
    qWarning() << "Fragment shader error:" << mProgram.log();
    close();
  }
  if (!mProgram.link()) {
    qWarning() << "Shader link error:" << mProgram.log();
    close();
  }
}

void s21::OpenGLWindow::initBuffer(const QString &nameFile) {
  if (mArrayBuffer.isCreated()) {
    mArrayBuffer.destroy();
  }
  if (mIndexBuffer.isCreated()) {
    mIndexBuffer.destroy();
  }
  // s21::FileParserFacade parser("C:/Users/Nikita/Downloads/Telegram
  // Desktop/one_million.obj");
  s21::FileParserFacade parser(
      nameFile.toStdString());  // здесь вводится путь до файла
  // s21::FileParserFacade parser("C:\\Users\\Nikita\\Downloads\\Telegram
  // Desktop\\cuberubik.obj");
  parser.processFile();
  countVertex = parser.getVertexCaunt();
  mArrayBuffer.create();
  mArrayBuffer.bind();  // делаем буфер активным
  mArrayBuffer.allocate(
      parser.getVertexes().data(),
      parser.getVertexes().size() * sizeof(float));  // заполняем буфер VBO
  mArrayBuffer.setUsagePattern(
      QOpenGLBuffer::DynamicDraw);  //Буфер будет изменяться и использоваться
                                    //много раз для отрисовки.
  mArrayBuffer.release();  // отсоиденяем буфер, делаем его не  активным

  mIndexBuffer.create();
  mIndexBuffer.bind();  // делаем буфер активным
  mIndexBuffer.allocate(parser.getIndexes().data(),
                        parser.getIndexes().size() *
                            sizeof(unsigned int));  // // заполняем буфер IBO
  mIndexBuffer.setUsagePattern(
      QOpenGLBuffer::DynamicDraw);  //Буфер будет изменяться и использоваться
                                    //много раз для отрисовки.
  mIndexBuffer.release();  // отсоиденяем буфер, делаем его не  активным
}

void s21::OpenGLWindow::mousePressEvent(
    QMouseEvent *event)  // событие на нажатие клавиши на мыши
{
  if (event->buttons() & Qt::LeftButton) {
    mMousePosition =
        QVector2D(event->position());  // запоминаем позицию нажатия клавиши
  }
  event->accept();  // явно указываем, что event сработал
}

void s21::OpenGLWindow::mouseMoveEvent(
    QMouseEvent *event)  // событие на движения указателя мыши
{
  if (!(event->buttons() & Qt::LeftButton))
    return;  // если нажата другая клавиша, то выходим

  QVector2D diff =
      QVector2D(event->position()) -
      mMousePosition;  // вычисляем разницу между местом нажатия клавиши и
                       // местом на которое мы перенесли указатель мыши
  mMousePosition =
      QVector2D(event->position());  // запоминаем новое положение мыши

  float angle = diff.length() /
                2.0;  // здесь вычисляем угол поворота. специально поделил на 2
                      // для того чтобы не так резко поворачивался обьект
  QVector3D axis =
      QVector3D(diff.y(), diff.x(),
                0.0);  // здесь задаем ось поворота оьекта, эта ось
                       // перпендикулярна вектору перемещения курсора мыши
  // в перпендикулярных векторах координаты (x) и (y) меняются местами и одна из
  // координат меняет знак, хнак нам менять не надо так как ось координат (y)
  // виджета направлена у нас вниз, а ось (y) в OpenGL направлена вверх
  mRotation = QQuaternion::fromAxisAndAngle(axis, angle) *
              mRotation;  //здесь задаем параметры нащего перемещения создавая
                          //оьект QQuaternion
  update();               // перерисовываем все
}
