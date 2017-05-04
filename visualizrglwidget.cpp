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

    initShaders();
}

bool VisualizrGLWidget::initShaders()
{
    shader_program = new QOpenGLShaderProgram();

    // vertex shader
    vertex_shader = new QOpenGLShader(QOpenGLShader::Vertex);
    vertex_shader->compileSourceFile(":/vert_shader.vert");
    if(!vertex_shader->isCompiled()) {
        qInfo() << "Failed to compile vertex shader:\n" << vertex_shader->log();
        return false;
    }

    // fragment shader
    fragment_shader = new QOpenGLShader(QOpenGLShader::Fragment);
    fragment_shader->compileSourceFile(":/frag_shader.frag");
    if(!fragment_shader->isCompiled()) {
        qInfo() << "Failed to compile fragment shader:\n" << fragment_shader->log();
        return false;
    }

    // link to program
    shader_program->addShader(vertex_shader);
    shader_program->addShader(fragment_shader);
    if(!shader_program->link()) {
        qInfo() << "Error linking shader program:\n" << shader_program->log();
        return false;
    }
    if(!shader_program->bind()) {
        qInfo() << "Error binding shader program:\n" << shader_program->log();
        return false;
    }
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

