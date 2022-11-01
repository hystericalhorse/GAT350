#version 430 core

in layout(location = 0) vec3 v_position; /* 0 */
in layout(location = 1) vec2 v_uv; /* 1 */
in layout(location = 2) vec3 v_normal; /* 2 */

out vec3 position;
out vec3 normal;
out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	uv = v_uv;

	mat4 model_view = view * model;
	normal = mat3(model_view) * v_normal;
	position = vec3(model_view * vec4(v_position, 1));

	mat4 mvp = projection * view * model;

	gl_Position = mvp * vec4(v_position, 1.0);
}
