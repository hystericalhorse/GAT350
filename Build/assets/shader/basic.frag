#version 430 core

in vec3 color;
out vec4 f_color;

uniform vec3 tint;

void main()
{
	f_color = vec4(color * tint, 1.0);
}
