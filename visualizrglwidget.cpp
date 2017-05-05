#include "visualizrglwidget.h"

VisualizrGLWidget::VisualizrGLWidget(QWidget* parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    setFormat(format);
}

void VisualizrGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glViewport(0, 0, width(), height());
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void VisualizrGLWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
}

void VisualizrGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

