#version 430 core 

in layout (location = 0) vec3 v_position;
in layout (location = 1) vec2 v_uv;

out vec2 uv;

uniform vec2 uv_tiling;
uniform vec2 uv_offset;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	uv = (v_uv * uv_tiling) + uv_offset;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(v_position, 1.0);
}
