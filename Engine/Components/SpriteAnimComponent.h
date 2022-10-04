#ifndef _COMPONENT_ANIMATED_SPRITE_H
#define _COMPONENT_ANIMATED_SPRITE_H

#include "RenderComponent.h"
#include "Renderer/Texture.h"
#include "Math/Rect.h"

#include <map>
#include <memory>

namespace en
{
	class SpriteAnimComponent : public RenderComponent
	{
	public:
		struct Sequence
		{
			std::string name;

			float fps = 0;
			int num_columns = 1;
			int num_rows = 1;

			int start_frame = 0;
			int end_frame = 0;

			bool loop = true;

			std::shared_ptr<en::Texture> texture = std::make_shared<en::Texture>();
		};

	public:
		SpriteAnimComponent() = default;

		CLONE(SpriteAnimComponent)

		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		Rect& _Source() override;
		void setSequence(const std::string& name);

	public:
		float fps = 0.0f;
		int columns, rows = 1;
		
		int start_frame = 0, end_frame = 0;
		int frame = 0;
		float frameTime = 0.0f;

		std::shared_ptr<en::Texture> _texture = std::make_shared<en::Texture>();
		Rect source;

		std::map<std::string, Sequence> _sequences;
		Sequence* _sequence = nullptr;

	};
}

#endif // _COMPONENT_ANIMATED_SPRITE_H