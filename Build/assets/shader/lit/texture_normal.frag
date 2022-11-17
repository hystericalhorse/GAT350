#version 430 core

#define POINT 0
#define DIRECTIONAL 1
#define SPOTLIGHT 2
#define MAX_LIGHTS 5

in vec2 uv;
in vec3 position;
in mat3 tbn;

out vec4 f_color;

/* Light */
uniform struct Light
{
	int   type;
	vec3  color;
	vec4  position;
	vec3  direction;
	float cutoff;
	float exponent;
} lights[MAX_LIGHTS];

uniform int light_count;
uniform vec3 ambient_color;

uniform vec3  m_color;
uniform float m_shininess;
uniform vec2  m_tiling;
uniform vec2  m_offset;

layout (binding = 0) uniform sampler2D diffuseMap; /* 0 Diffuse */
layout (binding = 1) uniform sampler2D normalMap; /* 1 Normal */

void phong(Light light, vec3 position, vec3 normal, out vec3 diffuse, out vec3 specular)
{
	vec3 light_direction = (light.type == DIRECTIONAL) ? normalize(-light.direction) : normalize(vec3(light.position) - position);
	
	// For SPOT Lights, Compute Intensity
	float spot_intensity = 1.0;
	if (light.type == SPOTLIGHT)
	{
		float cosine = dot(light.direction, -light_direction);
		float angle = acos(cosine);
		
		spot_intensity = (angle < light.cutoff) ? pow(cosine, light.exponent) : 0.0;
	}

	// Diffuse
	float intensity = max(dot(light_direction, normal), 0) * spot_intensity * 1.0; // possible implementation of intensity multiplier?
	diffuse = light.color * m_color * intensity;

	// Specular
	specular = vec3(0.0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_direction, normal);
	
		vec3 view_direction = normalize(-vec3(position));

		intensity = max(dot(reflection, view_direction), 0);
		intensity = pow(intensity, m_shininess);

		specular = light.color * m_color * intensity;
	}
}

void main()
{
	vec2 t_uv = (uv * m_tiling) + m_offset;

	Light light;

	vec3 normal = texture(normalMap, t_uv).rgb;
	normal = (normal * 2) - 1; // 0 - 1 -> -1 - 1
	normal = normalize(tbn * normal);

	f_color = vec4(ambient_color, 1) * texture(diffuseMap, t_uv);

	for (int i = 0; i < light_count; i++) 
	{ 
		vec3 diffuse; 
		vec3 specular; 
  
		phong(lights[i], position, normal, diffuse, specular); 
		f_color += (vec4(diffuse, 1.0) * texture(diffuseMap, t_uv)) + vec4(specular, 1.0); 
 } 
}