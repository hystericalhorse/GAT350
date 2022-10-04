#ifndef _RECT_H
#define _RECT_H

namespace en
{
	struct Rect
	{
		int x, y, w, h;

		int operator [] (size_t index) const { return (&x)[index]; }
		int& operator [] (size_t index) { return (&x)[index]; }
	};
}


#endif _RECT_H