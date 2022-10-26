#version 430 core

in vec2 uv;
in vec3 color;

out vec4 f_color;

uniform sampler2D textureSampler;

void main()
{
	f_color = texture(textureSampler, uv) * vec4(color, 1);
}
