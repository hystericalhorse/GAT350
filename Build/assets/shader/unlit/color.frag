#version 430 core

in vec3 color;

out vec4 f_color;

void main()
{
	f_color = vec4(color, 1);
}
