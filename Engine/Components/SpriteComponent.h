#ifndef _COMPONENT_SPRITE_H
#define _COMPONENT_SPRITE_H

#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Math/Rect.h"

namespace en
{
	class SpriteComponent : public RenderComponent
	{
	public:
		SpriteComponent() = default;

		CLONE(SpriteComponent)

		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<en::Texture> _texture = std::make_shared<en::Texture>();

	};
}

#endif // _COMPONENT_SPRITE_H