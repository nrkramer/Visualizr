#-------------------------------------------------
#
# Project created by QtCreator 2017-04-11T10:56:06
#
#-------------------------------------------------

QT       += core gui multimedia opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Visualizr
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    visualizrglwidget.cpp

HEADERS  += mainwindow.h \
    visualizrglwidget.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    vert_shader.vert
