#version 330
attribute vec3 position;
attribute vec4 color;

out vec4 vColor;

uniform mat4 mvp;

void main(void)
{
    gl_Position = mvp * vec4(position, 1.0);
    vColor = color;
}

