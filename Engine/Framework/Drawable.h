#ifndef _DRAWABLE_H
#define _DRAWABLE_H

#include "GameObject.h"
#include "Renderer/Model.h"

namespace en
{
	class Drawable : public en::GameObject
	{
	public:
		enum DrawableType
		{
			MODEL, POINT, CIRCLE
		};

	public:
		Drawable() = default;
		Drawable(const Transform& transform, const Model& model); // MODEL Drawable
		Drawable(const Transform& transform, Color& color); // POINT Drawable
		Drawable(const Transform& transform, float radius, Color& color); // CIRCLE Drawable

		CLONE(Drawable)

		void Draw(Renderer& renderer, const Vector2& offset);
		void Init() override {}
		void Update() override {}

	private:
		DrawableType _drawabletype;

		en::Model _model;
		Transform _transform;

		float _r = 0.0;
		en::Color _color;
	};
}

#endif // _DRAWABLE_H
