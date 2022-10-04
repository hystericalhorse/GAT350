#include "TilemapComponent.h"
#include "Engine.h"

namespace en
{
	void TilemapComponent::Init()
	{
		for (int i = 0; i < _tiles.size(); i++)
		{
			int index = _tiles[i];
			if (index == 0) continue;

			auto actor = en::Factory::Instance().Retrieve<en::Actor>(_tile_names[index]);
			if (actor)
			{
				int x = i % num_columns;
				int y = i / num_columns;

				actor->_Transform().position = _owner->_Transform().position + (Vector2{x, y} * size);
				_owner->getScene()->addActor(std::move(actor));
			}
		}
	}

	void TilemapComponent::Update()
	{

	}

	bool TilemapComponent::Write(const rapidjson::Value& value) const
	{
		// TODO

		return true;
	}

	bool TilemapComponent::Read(const rapidjson::Value& value)
	{
		std::vector<std::string>& tile_names = _tile_names;
		std::vector<int>& tiles = _tiles;

		READ_DATA(value, num_columns);
		READ_DATA(value, num_rows);
		READ_DATA(value, size);
		READ_DATA(value, tile_names);
		READ_DATA(value, tiles);

		return true;
	}

}