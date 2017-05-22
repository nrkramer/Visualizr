#ifndef CUBEPLUGIN_H
#define CUBEPLUGIN_H

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

#include "../Visualizr/visualizrplugin.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <GL/gl.h>
#include <GL/glu.h>

class CubePlugin : public QObject, VisualizrPlugin {
    Q_OBJECT
    Q_INTERFACES(VisualizrPlugin)
    Q_PLUGIN_METADATA(IID "Kramer.Visualizr.CubePlugin/1.0" FILE "cubeplugin.json")

public:
    CubePlugin();
    ~CubePlugin();

    QString pluginName();

    bool setVulkan(const bool &enabled);

    void draw();
    bool initialize();

    void setSize(const int &width, const int &height);

private:
    bool vulkan;

    const static float vertices[3*6*6];
    const static float colors[4*6*6];

    int width;
    int height;

    // OPENGL
    int mvp_location;
    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_perspective;
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer colorBuffer;

    QOpenGLShaderProgram *shader_program;

    bool initGL();
    void drawGL();
    bool initGLShaders();
    //void initVulkan();
};

#endif // CUBEPLUGIN_H
