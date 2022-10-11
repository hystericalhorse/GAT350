#ifndef _SHADER_H
#define _SHADER_H

#include "Resource/Resource.h"
#include "Renderer.h"

namespace en
{
	class Shader : public Resource
	{
	public:
		Shader() = default;
		~Shader();

		bool Create(std::string name, ...);

	public:
		GLuint _shader = 0;
	};
}

#endif // _SHADER_H