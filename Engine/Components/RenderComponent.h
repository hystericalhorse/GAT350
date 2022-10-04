#ifndef _COMPONENT_RENDER_H
#define _COMPONENT_RENDER_H

#include "Framework/Component.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"
#include <memory>

namespace en
{
	class Renderer;

	class RenderComponent : public Component
	{
	public:
		virtual void Draw(Renderer& renderer) = 0;

		virtual Rect& _Source() { return _source; }
		void Flip(bool flip = false) { _flipH = flip; }
		bool _Flip() { return _flipH; }
	private:
		Rect _source;
		bool _flipH = false;
		Vector2 _registration { 0.5f, 0.5f };

	};
}

#endif // _COMPONENT_RENDER_H