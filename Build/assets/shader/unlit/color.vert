#version 430 core 

in layout (location = 0) vec3 v_position;
in layout (location = 1) vec2 v_uv;

out vec3 color;

uniform vec3 m_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	color = m_color;

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(v_position, 1.0);
}
