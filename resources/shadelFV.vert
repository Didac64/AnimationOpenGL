#version 330 core
layout (location = 0) in vec3 p;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 ATexture;

out vec3 ourColor;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(p, 1.0);
	ourColor = color;
	TexCoord = ATexture;
}