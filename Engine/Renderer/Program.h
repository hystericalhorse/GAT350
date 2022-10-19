#ifndef _PROGRAM_H
#define _PROGRAM_H

#include "Renderer.h"
#include "Resource/Resource.h"
#include "Math/MathUtils.h"

#include <map>
#include <vector>

namespace en
{
	class Shader;

	class Program : public Resource
	{
	public:
		Program() = default;
		~Program();

		virtual bool Create(std::string name, ...) override;
		void newShader(const std::shared_ptr<en::Shader>& shader);

		void Link();
		void Use();

		void setUniform(const std::string& name, float val);
		void setUniform(const std::string& name, int val);
		void setUniform(const std::string& name, unsigned int val);
		void setUniform(const std::string& name, bool value);

		void setUniform(const std::string& name, const glm::vec2& val);
		void setUniform(const std::string& name, const glm::vec3& val);
		void setUniform(const std::string& name, const glm::vec4& val);

		void setUniform(const std::string& name, const glm::mat3& val);
		void setUniform(const std::string& name, const glm::mat4& val);

		GLuint _program = 0;
		std::vector<std::shared_ptr<en::Shader>> _shaders;
		std::map<std::string, GLint> _uniforms;

	private:
		GLint getUniform(const std::string& name);
	};
}

#endif // _PROGRAM_H