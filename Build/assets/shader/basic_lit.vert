#version 430 core

in layout(location = 0) vec3 v_position; /* 0 */
in layout(location = 1) vec2 v_uv; /* 1 */
in layout(location = 2) vec3 v_normal; /* 2 */

out vec2 uv;
out vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

/* Light */
uniform vec3 l_color;
uniform vec4 l_position;

void main()
{
	uv = v_uv;

	mat4 model_view = view * model;
	vec3 normal = mat3(model_view) * v_normal;
	vec4 position = model_view * vec4(v_position, 1);
	vec3 light_direction = normalize(vec3(l_position - position));

	float intensity = max(dot(light_direction, normal), 0);
	vec3 diffuse = l_color * intensity;

	color = vec3(1.0) + diffuse;

	mat4 mvp = projection * view * model;
	vec4 t_position = mvp * vec4(v_position, 1.0);

	gl_Position = t_position;
}
