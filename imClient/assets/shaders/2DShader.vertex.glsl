#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_texCoords;

out vec4 o_color;
out vec2 o_texCoords;

uniform mat4 u_PVM;

void main()
{
    gl_Position = u_PVM * vec4(a_pos, 1.0f);
    o_color = a_color;
    o_texCoords = a_texCoords;
}