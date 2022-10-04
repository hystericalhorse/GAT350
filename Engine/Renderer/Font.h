#ifndef _FONT_H
#define _FONT_H

#include <string>
#include "Resource/Resource.h"

struct _TTF_Font;
struct SDL_Surface;

namespace en
{
	struct Color;

	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(std::string filename, ...);
		void Load(const std::string& filename, int fontSize);

		SDL_Surface* CreateSurface(const std::string& text, const Color& color);

		friend class Text;

		_TTF_Font* _font = nullptr;
	};
}

#endif // _FONT_H