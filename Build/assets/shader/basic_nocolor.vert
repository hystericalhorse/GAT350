#version 430 core

in layout(location = 0) vec3 v_position; /* 0 */
in layout(location = 1) vec2 v_uv; /* 1 */

out vec2 uv;

uniform mat4 transform;
uniform mat4 mvp;

void main()
{
	uv = v_uv;
	vec4 t_position = mvp * vec4(v_position, 1.0);

	gl_Position = t_position;
}
