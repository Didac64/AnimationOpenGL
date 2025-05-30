#version 330 core

layout (location = 0) in vec3 p;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 Texture;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	
	gl_Position = vec4(p, 1.0);
	ourColor = color;
	TexCoord = vec2(Texture.x, Texture.y);

}