#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL_image.h>

namespace en
{
	Texture::~Texture()
	{
		if (_texture) glDeleteTextures(1, &_texture);
	}

	bool Texture::Create(Renderer& renderer, const std::string& filename)
	{
		SDL_Surface* _surface = IMG_Load(filename.c_str());
		if (_surface == nullptr) { LOG(SDL_GetError()); return false; }
		// flipSurface(_surface); // UVs are automatically flipped in Model.cpp

		glGenTextures(1, &_texture);
		glBindTexture(_target, _texture);

		GLenum format = (_surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(_target, 0, format, _surface->w, _surface->h, 0, format, GL_UNSIGNED_BYTE, _surface->pixels);

		glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // GL_NEAREST FOR RETRO LOOK, GL_LINEAR FOR SMOOTHER TEXTURE
		glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(_target, GL_TEXTURE_WRAP_T, GL_REPEAT);

		SDL_FreeSurface(_surface);

		return true;
	}

	bool Texture::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Texture::Create(renderer, filename);
	}

	en::Vector2 Texture::getSize() const
	{
		return Vector2{ 0 , 0 };
	}

	void Texture::flipSurface(SDL_Surface* surface)
	{
		SDL_LockSurface(surface);

		int pitch = surface->pitch;
		uint8_t* t = new uint8_t[pitch];
		uint8_t* pixels = (uint8_t*) surface->pixels;

		for (int i = 0; i < surface->h / 2; ++i) {
			uint8_t* row1 = pixels + i * pitch;
			uint8_t* row2 = pixels + (surface->h - i - 1) * pitch;

			memcpy(t, row1, pitch);
			memcpy(row1, row2, pitch);
			memcpy(row2, t, pitch);
		}

		delete[] t;

		SDL_UnlockSurface(surface);
	}

	/** Deprecated ***************************************************************

	Texture::~Texture()
	{
		if (_texture) SDL_DestroyTexture(_texture);
	}

	bool Texture::Create(Renderer& renderer, const std::string& filename)
	{
		SDL_Surface* _surface = IMG_Load(filename.c_str());
		if (_surface == nullptr) { LOG(SDL_GetError()); return false; }
		_texture = SDL_CreateTextureFromSurface(renderer._renderer, _surface);
		if (_texture == nullptr) { LOG(SDL_GetError()); return false; }
		SDL_FreeSurface(_surface);

		return true;
	}

	bool Texture::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);

		Renderer& renderer = va_arg(args, Renderer);

		va_end(args);

		return Texture::Create(renderer, filename);
	}

	bool Texture::CreateFromSurface(SDL_Surface* surface, Renderer& renderer)
	{
		if (_texture) SDL_DestroyTexture(_texture);
		
		_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);
		SDL_FreeSurface(surface);

		if (!_texture)
		{
			LOG(SDL_GetError());
			return false;
		}

		return true;
	}

	en::Vector2 Texture::getSize() const
	{
		SDL_Point point{};
		SDL_QueryTexture(_texture, nullptr, nullptr, &point.x, &point.y);

		return Vector2{ point.x , point.y };
	}

	********************************************************************/
}