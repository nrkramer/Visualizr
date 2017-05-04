#ifndef VISUALIZRGLWIDGET_H
#define VISUALIZRGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLContext>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QMatrix4x4>
#include <GL/gl.h>
#include <GL/glu.h>

class VisualizrGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    VisualizrGLWidget(QWidget* parent);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    bool initShaders();

private:
    QMatrix4x4 m_projection; // projection matrix

    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer vbo;
    QOpenGLShaderProgram *shader_program;
    QOpenGLShader *vertex_shader;
    QOpenGLShader *fragment_shader;
};

#endif // VISUALIZRGLWIDGET_H
