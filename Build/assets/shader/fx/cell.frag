#version 430 core

#define POINT 0
#define DIRECTIONAL 1
#define SPOTLIGHT 2

in vec2 uv;
in vec4 position;
in vec3 normal;

out vec4 f_color;

/* Light */
uniform int   l_type;
uniform vec3  l_ambient;
uniform vec3  l_color;
uniform vec4  l_position;
uniform vec3  l_direction;
uniform float l_cutoff;
uniform float l_exponent;

uniform vec3 m_color;
uniform vec2 m_tiling;
uniform vec2 m_offset;

int levels = 3;
const float scalef = 1.0 / levels;

void phong(vec4 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	// Light Direction
	vec3 light_direction = (l_type == DIRECTIONAL) ? normalize(-l_direction) : normalize(vec3(l_position - position));
	
	// For SPOT Lights, Compute Intensity
	float spot_intensity = 1.0;
	if (l_type == SPOTLIGHT)
	{
		float cosine = dot(l_direction, -light_direction);
		float angle = acos(cosine);
		
		spot_intensity = (angle < l_cutoff) ? pow(cosine, l_exponent) : 0.0;
	}

	// Ambient
	ambient = l_ambient * m_color;

	float intensity = max(dot(light_direction, normal), 0);
	intensity = floor(levels * intensity) * scalef;
	diffuse = l_color * intensity;

	// Specular
	specular = vec3(0.0);
}

void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	phong(position, normal, ambient, diffuse, specular);

	vec2 t_uv = (uv * m_tiling) + m_offset;

	f_color = vec4(ambient + diffuse, 1.0) + (vec4(specular, 1.0));
}