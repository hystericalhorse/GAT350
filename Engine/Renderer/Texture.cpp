#include "Texture.h"
#include "Renderer.h"
#include "Core/Logger.h"
#include <SDL_image.h>

namespace en
{
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
}