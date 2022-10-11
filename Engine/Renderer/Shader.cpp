#include "Shader.h"

#include "Core/File.h"
#include "Core/Logger.h"

namespace en
{
	Shader::~Shader()
	{
		if (!_shader)
		{
			glDeleteShader(_shader);
		}
	}

	bool Shader::Create(std::string name, ...)
	{
		std::string source;
		bool success = readFile(name, source);
		if (!success)
		{
			LOG("error reading shader file %s.", name.c_str());
		}

		// get shader type arguments
		va_list args;
		va_start(args, name);
		GLuint shaderType = va_arg(args, GLuint);
		va_end(args);

		// create shader
		_shader = glCreateShader(shaderType);

		// compile shader
		const char* source_c = source.c_str();
		glShaderSource(_shader, 1, &source_c, NULL);
		glCompileShader(_shader);

		// check shader compilation status
		GLint status;
		glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE)
		{
			// display shader error
			GLint length = 0;
			glGetShaderiv(_shader, GL_INFO_LOG_LENGTH, &length);

			if (length > 0)
			{
				std::string infoLog(length, ' ');
				glGetShaderInfoLog(_shader, length, &length, &infoLog[0]);
				LOG("failed to compile shader %s.", name.c_str());
				LOG("shader info: %s", infoLog.c_str());
			}

			// delete shader
			glDeleteShader(_shader);
			_shader = 0;
		}

		return true;
	}
}