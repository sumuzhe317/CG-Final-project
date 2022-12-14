// Firework' Vertex Shader (Flat shading)
#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 Color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 vertexColor;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	Color = vertexColor;
}