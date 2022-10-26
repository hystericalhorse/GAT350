#include "Program.h"
#include "Engine.h"

namespace en
{
	Program::~Program()
	{
		if (_program) glDeleteProgram(_program);
	}

	bool Program::Create(std::string name, ...)
	{
		rapidjson::Document document;

		bool success = en::json::Load(name, document);
		if (!success)
		{
			LOG("Could not load file %s", name.c_str());
			return false;
		}

		_program = glCreateProgram();

		std::string vertex_shader;
		READ_DATA(document, vertex_shader);
		if (!vertex_shader.empty())
		{
			auto v_sh = __registry.Get<en::Shader>(vertex_shader, GL_VERTEX_SHADER);
			newShader(v_sh);
		}

		std::string fragment_shader;
		READ_DATA(document, fragment_shader);
		if (!fragment_shader.empty())
		{
			auto f_sh = __registry.Get<en::Shader>(fragment_shader, GL_FRAGMENT_SHADER);
			newShader(f_sh);
		}

		this->Link();

		return true;
	}

	void Program::newShader(const std::shared_ptr<en::Shader>& shader)
	{
		_shaders.push_back(shader);

		glAttachShader(_program, shader->_shader);
	}

	void Program::Link()
	{
		glLinkProgram(_program);

		GLint status;
		glGetProgramiv(_program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint length = 0;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &length);

			if (length > 0)
			{
				std::string infoLog(length, ' ');
				glGetProgramInfoLog(_program, length, &length, &infoLog[0]);

				LOG("Failed to link program.");
				LOG("Info: %s", infoLog.c_str());

				glDeleteProgram(_program);
				_program = 0;
			}
		}
	}

	void Program::Use()
	{
		glUseProgram(_program);
	}

	GLint Program::getUniform(const std::string& name)
	{
		auto uniform = _uniforms.find(name);
		if (uniform == _uniforms.end())
		{
			GLint loc = glGetUniformLocation(_program, name.c_str());
			if (loc == -1)
			{
				LOG("Could not find location of uniform %s", name.c_str());
			}
			
			_uniforms[name] = loc;
		}

		return _uniforms[name];
	}

	void Program::setUniform(const std::string& name, float val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniform1f(uniform, val);
	}
	void Program::setUniform(const std::string& name, int val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniform1i(uniform, val);
	}
	void Program::setUniform(const std::string& name, unsigned int val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniform1ui(uniform, val);
	}
	void Program::setUniform(const std::string& name, bool val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniform1i(uniform, val);
	}

	void Program::setUniform(const std::string& name, const glm::vec2& val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniform2fv(uniform, 1, &val[0]);
	}
	void Program::setUniform(const std::string& name, const glm::vec3& val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniform3fv(uniform, 1, &val[0]);
	}
	void Program::setUniform(const std::string& name, const glm::vec4& val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniform4fv(uniform, 1, &val[0]);
	}

	void Program::setUniform(const std::string& name, const glm::mat3& val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniformMatrix3fv(uniform, 1, GL_FALSE, glm::value_ptr(val));
	}
	void Program::setUniform(const std::string& name, const glm::mat4& val)
	{
		GLint uniform = getUniform(name);
		if (uniform != -1) glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(val));
	}
}