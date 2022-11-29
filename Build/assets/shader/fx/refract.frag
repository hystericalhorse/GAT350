#version 430 core

in vec3 refraction_dir;

out vec4 f_color;

uniform samplerCube cubeMap; /* Cubemap */

void main()
{
	

	f_color = texture(cubeMap, refraction_dir);
}