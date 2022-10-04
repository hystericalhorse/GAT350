#ifndef _TEXT_H
#define _TEXT_H

#include <string>

struct SDL_Texture;

namespace en
{
	class Renderer;
	class Font;
	struct Color;
	struct Vector2;

	class Text
	{
	public:
		Text() = default;
		Text(Font* font) :
			_font{ font }
		{}
		~Text();

		void Create(Renderer& renderer, const std::string& text, const Color& color);
		void Draw(Renderer& renderer, const Vector2& position);

	private:
		Font* _font = nullptr;
		SDL_Texture* _texture = nullptr;

	};
}

#endif _TEXT_H