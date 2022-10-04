#ifndef _COLOR_H
#define _COLOR_H

#include <istream>
#include <string>

namespace en
{
	using u8_t = unsigned char;

	struct Color
	{
		Color() = default;
		Color(u8_t r, u8_t g, u8_t b, u8_t a) :
			r {r}, g{g}, b{b}, a{a}
		{}

		u8_t operator [] (size_t index) const { return (&r)[index]; }
		u8_t& operator [] (size_t index) { return (&r)[index]; }

		inline Color operator = (const Color& c)
		{
			this->r = c.r;
			this->g = c.g;
			this->b = c.b;
			this->a = c.a;

			return *this;
		}

		inline bool operator == (const Color& c)
		{
			if (this->r != c.r) return false;
			if (this->g != c.g) return false;
			if (this->b != c.b) return false;
			if (this->a != c.a) return false;

			return true;
		}

		inline bool operator != (const Color& c)
		{
			if (this->r != c.r) return true;
			if (this->g != c.g) return true;
			if (this->b != c.b) return true;
			if (this->a != c.a) return true;

			return false;
		}

		u8_t r, g, b, a;
	};

	static const Color white{ 255, 255, 255, 255 };
	static const Color black{ 0, 0, 0, 255 };
	static const Color red{ 255, 0, 0, 255 };
	static const Color orange{ 255, 165, 0, 255 };
	static const Color yellow{ 0, 255, 255, 255 };
	static const Color green{ 0, 255, 0, 255 };
	static const Color blue{ 0, 0, 255, 255 };
	static const Color indigo{ 75, 0, 130, 255 };
	static const Color violet{ 255, 0, 255, 255 };

	std::istream& operator >> (std::istream& stream, Color& c);
	std::ostream& operator << (std::ostream& stream, const Color& c);
}

#endif // _COLOR_H