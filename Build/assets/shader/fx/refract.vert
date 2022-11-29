#version 430 core

in layout(location = 0) vec3 v_position; /* 0 */
in layout(location = 2) vec3 v_normal; /* 2 */

out vec3 refraction_dir;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	vec3 position = vec3(model * vec4(v_position, 1));
	vec3 normal = normalize(mat3(model) * v_normal);

	vec3 camera_pos = vec3(inverse(view)[3]);

	vec3 view_dir = position - camera_pos;
	refraction_dir = refract(view_dir, normal, 1.0/1.5);

	mat4 vp = projection * view * model;

	gl_Position = vp * vec4(v_position, 1.0);
}
