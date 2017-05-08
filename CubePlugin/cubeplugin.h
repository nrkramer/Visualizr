#ifndef CUBEPLUGIN_H
#define CUBEPLUGIN_H

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

#include "cubeplugin_global.h"
#include "../Visualizr/visualizrplugin.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <GL/gl.h>
#include <GL/glu.h>

class CubePlugin : public VisualizrPlugin {
    Q_INTERFACES(VisualizrPlugin)
    Q_PLUGIN_METADATA(IID "Kramer.Visualizr.CubePlugin")

public:
    CubePlugin();
    virtual ~CubePlugin();

    QString pluginName();

    bool setVulkan(const bool &enabled);

    void draw();
    bool initialize();

private:
    bool vulkan;

    const static float vertices[3*6*6];
    const static float colors[4*6*6];

    // OPENGL
    QMatrix4x4 rotation;
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
