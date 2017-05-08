#include "cubeplugin.h"

CubePlugin::CubePlugin()
{
}

CubePlugin::~CubePlugin()
{
    vao.destroy();
    vertexBuffer.destroy();
    colorBuffer.destroy();

    delete shader_program;
}

QString CubePlugin::pluginName()
{
    return QString("Cube");
}

bool CubePlugin::setVulkan(const bool &enabled)
{
    vulkan = false;

    return false; // disabled for now
}

void CubePlugin::draw()
{
    drawGL();
}

bool CubePlugin::initialize()
{
    return initGL();
}

bool CubePlugin::initGL()
{
    vertexBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    colorBuffer = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);

    // create shaders
    if (!initGLShaders()) {
        qDebug() << "Error initializing shaders. Exiting.\n";
        return false;
    }

    shader_program->bind();

    // create vertex buffer
    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer.allocate((void*)vertices, ARRAY_SIZE(vertices));

    // create color buffer
    colorBuffer.create();
    colorBuffer.bind();
    colorBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    colorBuffer.allocate((void*)colors, ARRAY_SIZE(colors));

    // create vertex array object
    vao.create();
    vao.bind();
    shader_program->enableAttributeArray("position");
    shader_program->setAttributeBuffer("position", GL_FLOAT, 0, 3);
    shader_program->enableAttributeArray("color");
    shader_program->setAttributeBuffer("color", GL_FLOAT, 0, 4);

    // release
    colorBuffer.release();
    vertexBuffer.release();
    vao.release();
    shader_program->release();

    return true;
}

void CubePlugin::drawGL()
{
    shader_program->bind();
    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, ARRAY_SIZE(vertices));
    vao.release();
    shader_program->release();
}

bool CubePlugin::initGLShaders()
{
    shader_program = new QOpenGLShaderProgram();

    // vertex shader
    QOpenGLShader vertex_shader(QOpenGLShader::Vertex);
    vertex_shader.compileSourceFile(":shaders/vertex_shader.vert");
    if(!vertex_shader.isCompiled()) {
        qDebug() << "Failed to compile vertex shader:\n" << vertex_shader.log();
        return false;
    }

    // fragment shader
    QOpenGLShader fragment_shader(QOpenGLShader::Fragment);
    fragment_shader.compileSourceFile(":shaders/fragment_shader.frag");
    if(!fragment_shader.isCompiled()) {
        qDebug() << "Failed to compile fragment shader:\n" << fragment_shader.log();
        return false;
    }

    // link to program
    shader_program->addShader(&vertex_shader);
    shader_program->addShader(&fragment_shader);
    if(!shader_program->link()) {
        qDebug() << "Error linking shader program:\n" << shader_program->log();
        return false;
    }

    return true;
}

const float CubePlugin::vertices[] = {
    //RIGHT
    1.0, 1.0, 1.0,		//A first vertex
    1.0, -1.0, 1.0,		//A second vertex
    1.0, -1.0, -1.0,	//A third vertex
    1.0, -1.0, -1.0,	//B first vertex
    1.0, 1.0, -1.0,		//B second vertex
    1.0, 1.0, 1.0,		//B third vertex

    //LEFT
    -1.0, -1.0, -1.0,   //C first vertex
    -1.0, -1.0, 1.0,	//C second vertex
    -1.0, 1.0, 1.0,     //C third vertex
    -1.0, 1.0, 1.0,     //D first vertex
    -1.0, 1.0, -1.0,	//D second vertex
    -1.0, -1.0, -1.0,   //D third vertex

    //FRONT
    -1.0, 1.0, 1.0, 	//G first vertex
    -1.0, -1.0, 1.0,    //G second vertex
    1.0, -1.0, 1.0,		//G third vertex
    1.0, -1.0, 1.0,		//H first vertex
    1.0, 1.0, 1.0,		//H second vertex
    -1.0, 1.0, 1.0,		//H third vertex

    //BACK
    1.0, -1.0, -1.0,	//E first vertex
    -1.0, -1.0, -1.0,	//E second vertex
    -1.0, 1.0, -1.0,	//E third vertex
    -1.0, 1.0, -1.0,	//F first vertex
    1.0, 1.0, -1.0,		//F second vertex
    1.0, -1.0, -1.0,	//F third vertex

    //TOP
    -1.0, 1.0, 1.0, 	//I first vertex
    1.0, 1.0, 1.0,		//I second vertex
    1.0, 1.0, -1.0,		//I third vertex
    1.0, 1.0, -1.0,		//J first vertex
    -1.0, 1.0, -1.0,	//J second vertex
    -1.0, 1.0, 1.0,		//J third vertex

    //BOTTOM
    1.0, -1.0, -1.0, 	//K first vertex
    1.0, -1.0, 1.0,		//K second vertex
    -1.0, -1.0, 1.0,	//K third vertex
    -1.0, -1.0, 1.0,	//L first vertex
    -1.0, -1.0, -1.0,	//L second vertex
    1.0, -1.0, -1.0		//L third vertex
};

const float CubePlugin::colors[] = {
    1.0, 0.0, 0.0, 1.0, // front
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0, // top
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, // left
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0, // right
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, // back
    1.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 0.0, 1.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 1.0, 1.0, // bottom
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0,
    1.0, 0.0, 0.0, 1.0
};
