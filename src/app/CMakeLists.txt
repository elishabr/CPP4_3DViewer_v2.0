cmake_minimum_required(VERSION 3.14)

project(testapp LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS QuickWidgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS OpenGL)

add_executable(testapp
  main.cpp
  widget.h widget.cpp

  resource.qrc
  fileparserfacade.cpp fileparserfacade.h openglwindow.cpp openglwindow.h
)

qt_add_qml_module(testapp
    URI TestApp
    VERSION 1.0
    QML_FILES ListButtone.qml main.qml TitleLabel.qml TextButtone.qml
    QML_FILES ColorButtone.qml
    QML_FILES ListButtoneForSize.qml
    QML_FILES MySlider.qml
)

target_link_libraries(testapp
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::OpenGLWidgets
    PRIVATE Qt6::OpenGL
    PRIVATE Qt6::QuickWidgets
)

include(GNUInstallDirs)
install(TARGETS testapp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
