#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "Resource/Resource.h" 
#include "Math/MathUtils.h"

#include <vector> 
#include <memory>

namespace en
{
	class Texture;
	class Program;

	class Material : public Resource
	{
	public:
		virtual bool Create(std::string name, ...) override;
		void Link();
		void Bind();
		std::shared_ptr<en::Program> getProgram() { return _program; }

		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess = 0.0f;

	private:
		std::shared_ptr<en::Program> _program;
		std::vector<std::shared_ptr<en::Texture>> _textures;

	};

}

#endif // _MATERIAL_H