#version 430 core

in vec2 uv;
in vec4 position;
in vec3 normal;

out vec4 f_color;

/* Light */
uniform vec3 l_ambient;
uniform vec3 l_color;
uniform vec4 l_position;

uniform vec3 m_color;
uniform float m_shininess;
uniform vec2 m_tiling;
uniform vec2 m_offset;

layout (binding = 0) uniform sampler2D texture_1; /* 0 Diffuse */
layout (binding = 1) uniform sampler2D texture_2; /* 1 Specular */
layout (binding = 2) uniform sampler2D texture_3; /* 2 Emissive */

void phong(vec4 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	// Ambient
	ambient = l_ambient * m_color;

	// Diffuse
	vec3 light_direction = normalize(vec3(l_position - position));

	float intensity = max(dot(light_direction, normal), 0);
	diffuse = l_color * intensity;

	// Specular
	specular = vec3(0.0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_direction, normal);
	
		vec3 view_direction = normalize(-vec3(position));

		intensity = max(dot(reflection, view_direction), 0);
		intensity = pow(intensity, m_shininess);

		specular = l_color * m_color * intensity;
	}
}

void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	phong(position, normal, ambient, diffuse, specular);

	vec2 t_uv = (uv * m_tiling) + m_offset;

	f_color = texture(texture_3, t_uv) + vec4(ambient + diffuse, 1.0) * texture(texture_1, t_uv) + (vec4(specular, 1.0) * texture(texture_2, t_uv));
}