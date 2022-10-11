#version 430 core

in vec3 v_position; /* 0 */
in vec3 v_color; /* 1 */

out vec3 color;

void main()
{
	gl_Position = vec4(v_position, 1.0);

	color = v_color;
}
