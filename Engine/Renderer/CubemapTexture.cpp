#include "CubemapTexture.h"
#include "Core/Logger.h"
#include "Renderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <cstdarg>

#include <array>

namespace en
{
	bool CubemapTexture::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);

		std::string& extension = va_arg(args, std::string);

		va_end(args);

		std::vector<std::string> filenames = genCubemapNames(filename, extension);

		return CubemapTexture::Load(filenames);
	}

	bool CubemapTexture::Load(const std::vector<std::string>& filenames)
	{
		_target = GL_TEXTURE_CUBE_MAP;

		glGenTextures(1, &_texture);
		glBindTexture(_target, _texture);

		GLuint targets[] =
		{
			GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		for (size_t i = 0; i < filenames.size(); i++)
		{
			SDL_Surface* surface = IMG_Load(filenames[i].c_str());
			if (surface == nullptr)
			{
				LOG(SDL_GetError());
				return false;
			}

			LOG("%s : width = %d | height = %d | pixel format = %s", filenames[i].c_str(), surface->w, surface->h, SDL_GetPixelFormatName(surface->format->format));

			GLenum internalFormat = getInternalFormat(surface->format->format);
			GLint format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

			glTexImage2D(targets[i], 0, format, surface->w, surface->h, 0, internalFormat, GL_UNSIGNED_BYTE, surface->pixels);
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_TEXTURE_CUBE_MAP_SEAMLESS);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_TEXTURE_CUBE_MAP_SEAMLESS);

		return true;;
	}

	std::vector<std::string> CubemapTexture::genCubemapNames(const std::string& basename, const std::string& extension)
	{
		std::array<std::string, 6> suffixes = { "posx", "negx", "posy", "negy", "posz", "negz" };

		std::vector<std::string> names;
		for (size_t i = 0; i < suffixes.size(); i++)
		{
			std::string name = basename + suffixes[i] + extension;
			names.push_back(name);
		}

		return names;
	}
}