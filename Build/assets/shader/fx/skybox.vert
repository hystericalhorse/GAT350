#version 430 core

in layout(location = 0) vec3 v_position; /* 0 */

out vec3 uv;

uniform mat4 view;
uniform mat4 projection;


void main()
{
	uv = v_position;

	mat4 vp = projection * mat4(mat3(view));

	gl_Position = vp * vec4(v_position, 1.0);
}
