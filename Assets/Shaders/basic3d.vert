#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoord;

uniform mat4 u_viewProjection;
uniform mat4 u_model;

out vec3 v_worldPosition;
out vec3 v_normal;
out vec2 v_texCoord;

void main()
{
    vec4 worldPosition = u_model * vec4(a_position, 1.0);

    v_worldPosition = worldPosition.xyz;
    v_normal = mat3(u_model) * a_normal;
    v_texCoord = a_texCoord;

    gl_Position = u_viewProjection * worldPosition;
}