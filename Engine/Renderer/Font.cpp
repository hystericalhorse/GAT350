#include "Font.h"

#include "Math/Color.h"
#include "Core/Logger.h"
#include <SDL_ttf.h>

namespace en
{
	Font::Font(const std::string& filename, int fontSize)
	{
		this->Load(filename, fontSize);
	}

	Font::~Font()
	{
		// Troubleshooting issues with _font not closing properly.
		// Unhandled Exception, Access Reading Violation

		// _font is apparently empty.

		/*
		if (_font)
		{
			TTF_CloseFont(_font);
		}
		*/
	}

	bool Font::Create(std::string filename, ...)
	{
		va_list args;
		va_start(args, filename);

		int fontSize = va_arg(args, int);
	
		va_end(args);

		Font::Load(filename, fontSize);

		return true;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		this->_font = TTF_OpenFont(filename.c_str(), fontSize);
	}

	SDL_Surface* Font::CreateSurface(const std::string& text, const Color& color)
	{
		SDL_Color c {color.r, color.g, color.b, color.a};
		SDL_Surface* surface = TTF_RenderText_Solid(_font, text.c_str(), c);

		if (!surface)
		{
			LOG(SDL_GetError());
		}

		return surface;
	}
}