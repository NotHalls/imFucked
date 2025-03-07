#version 460 core

out vec4 FragColor;

in vec4 o_color;
in vec2 o_texCoords;

uniform sampler2D u_Texture;

void main()
{                
    FragColor = texture(u_Texture, o_texCoords);
}