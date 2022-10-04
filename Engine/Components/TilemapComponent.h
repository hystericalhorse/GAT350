#ifndef _COMPONENT_TILEMAP_H
#define _COMPONENT_TILEMAP_H

#include "RenderComponent.h"
#include "Math/Rect.h"
#include "Math/Vector2.h"
#include <vector>

namespace en
{
	class TilemapComponent : public Component
	{
		CLONE(TilemapComponent)

		virtual void Init() override;
		virtual void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;


	private:
		int num_columns = 0;
		int num_rows = 0;
		Vector2 size;

		std::vector<std::string> _tile_names;
		std::vector<int> _tiles;
	};
}

#endif // _COMPONENT_TILEMAP_H