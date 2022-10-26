#version 430 core

in vec2 uv;

out vec4 f_color;

uniform sampler2D textureSampler;

void main()
{
	f_color = texture(textureSampler, uv);
}
