#include "visualizrglwidget.h"

VisualizrGLWidget::VisualizrGLWidget(QWidget* parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setVersion(3, 3);
    setFormat(format);
}

bool VisualizrGLWidget::setRenderPlugin(VisualizrPlugin *plugin)
{
    plugin->setSize(width(), height());
    bool status = plugin->initialize();
    if (status) {
        currentPlugin = plugin;
        qInfo() << "Loaded " << plugin->pluginName() << " plugin.";
    } else {
        qDebug() << "Error loading " << plugin->pluginName();
    }

    return status;
}

void VisualizrGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glViewport(0, 0, width(), height());
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);

    emit glReady();
}

void VisualizrGLWidget::resizeGL(int w, int h)
{
    currentPlugin->setSize(w, h);
}

void VisualizrGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    currentPlugin->draw();
}

