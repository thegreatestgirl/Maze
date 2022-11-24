# QT       += core gui opengl openglwidgets

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    view/cavewidget.cpp \
    view/glwidget.cpp \
    view/mainwindow.cpp \
    model/cave.cpp \
    model/cave_parser.cpp \
    model/cell.cpp \
    model/maze_cell.cpp \
    model/cave_cell.cpp \
    model/maze.cpp \
    model/parser.cpp \
    model/model.cpp \
    controller/controller.cpp

HEADERS += \
    view/cavewidget.h \
    view/glwidget.h \
    view/mainwindow.h \
    model/cave.h \
    model/cave_parser.h \
    model/cell.h \
    model/maze_cell.h \
    model/cave_cell.h \
    model/exceptions.h \
    model/matrix.h \
    model/maze.h \
    model/parser.h \
    model/model.h \
    model/field.h \
    controller/controller.h

FORMS += \
    view/mainwindow.ui

# LIBS += -framework GLUT -framework OpenGL -framework Cocoa
LIBS += -lglut -lGLU

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../maze.txt
