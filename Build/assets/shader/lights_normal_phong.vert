#version 430 core

in layout(location = 0) vec3 v_position; /* 0 */
in layout(location = 1) vec2 v_uv; /* 1 */
in layout(location = 2) vec3 v_normal; /* 2 */
in layout(location = 3) vec3 v_tangent; /* 3 */

out vec3 position;
out vec2 uv;
out mat3 tbn; // Tangent, Bitangent, Normal

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()
{
	uv = v_uv;
	mat4 model_view = view * model;

	vec3 normal = normalize(mat3(model_view) * v_normal);
	vec3 tangent = normalize(mat3(model_view) * v_tangent);
	vec3 bitangent = cross(normal, tangent);

	tbn = mat3(tangent, bitangent, normal);

	position = vec3(model_view * vec4(v_position, 1));

	mat4 mvp = projection * view * model;

	gl_Position = mvp * vec4(v_position, 1.0);
}
