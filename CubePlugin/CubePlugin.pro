#-------------------------------------------------
#
# Project created by QtCreator 2017-05-04T15:01:59
#
#-------------------------------------------------

QT       += opengl

QT       -= core gui

TARGET = CubePlugin
TEMPLATE = lib
CONFIG += plugin

DEFINES += CUBEPLUGIN_LIBRARY

SOURCES += cubeplugin.cpp

HEADERS += cubeplugin.h\
    ../Visualizr/visualizrplugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    resources.qrc

DISTFILES += \
    vertex_shader.vert \
    fragment_shader.frag \
    cubeplugin.json
