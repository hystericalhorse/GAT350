#include "Text.h"
#include "Font.h"
#include "Renderer.h"

#include <SDL.h>
#include <SDL_ttf.h>

namespace en
{
	Text::~Text()
	{
		if (_texture)
		{
			SDL_DestroyTexture(_texture);
		}
	}

	void Text::Create(Renderer& renderer, const std::string& text, const Color& color)
	{
		SDL_Color c {color.r, color.g, color.b, color.a};
		SDL_Surface* surface = TTF_RenderText_Solid(_font->_font, text.c_str(), c);

		_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface);
		SDL_FreeSurface(surface);
	}

	void Text::Draw(Renderer& renderer, const Vector2& position)
	{
		int width, height;
		SDL_QueryTexture(_texture, nullptr, nullptr, &width, &height);

		SDL_Rect rect { (int)position.x, (int)position.y, width, height };

		SDL_RenderCopy(renderer._renderer, _texture, NULL, &rect);

	}
}