#include "Background.h"

namespace en
{

	Background::~Background() {}

	void Background::Draw(Renderer& renderer, const Vector2& offset)
	{
		for (size_t i = 0; i < _elements.size(); i++)
		{
			_elements[i].Draw(renderer, offset);
		}
	}

	void Background::newElement(Transform& transform, const Model& model)
	{
		Drawable drawable(transform, model);
		_elements.push_back(drawable);
	}

	void Background::newElement(Transform& transform, Color& color)
	{
		Drawable drawable(transform, color);
		_elements.push_back(drawable);
	}

	void Background::newElement(Transform& transform, float radius, Color& color)
	{
		Drawable drawable(transform, radius, color);
		_elements.push_back(drawable);
	}
}