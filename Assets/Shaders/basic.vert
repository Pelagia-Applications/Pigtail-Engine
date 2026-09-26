#version 330 core

layout(location = 0) in vec2 a_position;

uniform mat4 u_viewProjection;
uniform mat4 u_model;

void main()
{
    gl_Position =
        u_viewProjection *
        u_model *
        vec4(a_position, 0.0, 1.0);
}