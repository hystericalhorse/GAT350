#version 430 core

in vec3 color;
in vec2 uv;

out vec4 f_color;

uniform vec3 tint;
uniform sampler2D textureSampler;

void main()
{
	// f_color = vec4(color * tint, 1.0);
	f_color = texture(textureSampler, uv);
}
