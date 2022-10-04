#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "Framework/Drawable.h"

#include <vector>

namespace en
{
	class Background
	{
	public:
		Background() = default;
		~Background();

		void Draw(Renderer& renderer, const Vector2& offset);
		void newElement(Transform& transform, const Model& model); // MODEL Drawable
		void newElement(Transform& transform, Color& color); // POINT Drawable
		void newElement(Transform& transform, float radius, Color& color); // CIRCLE Drawable

	private:
		std::vector<Drawable> _elements;

	};
}

#endif // _BACKGROUND_H