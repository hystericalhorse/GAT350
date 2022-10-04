#include "SpriteAnimComponent.h"
#include "Engine.h"

namespace en
{
	void SpriteAnimComponent::Update()
	{
		frameTime += __time.ci_time;
		if (frameTime >= 1.0f / _sequence->fps)
		{
			frameTime = 0;
			frame++;
			if (frame > _sequence->end_frame)
			{
				frame = (_sequence->loop) ? _sequence->start_frame : _sequence->end_frame;
			}
		}
	}

	void SpriteAnimComponent::Draw(Renderer& renderer)
	{
		renderer.Draw(_sequence->texture, _Source(), _owner->_Transform());
	}

	bool SpriteAnimComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool SpriteAnimComponent::Read(const rapidjson::Value& value)
	{
		if (value.HasMember("sequences") && value["sequences"].IsArray())
		{
			for (auto& sequenceValue : value["sequences"].GetArray())
			{
				Sequence sequence;

				std::string& name = sequence.name;
				float& fps = sequence.fps;
				int& columns = sequence.num_columns;
				int& rows = sequence.num_rows;
				int& start_frame = sequence.start_frame;
				int& end_frame = sequence.end_frame;

				READ_DATA(sequenceValue, name);
				READ_DATA(sequenceValue, fps);
				READ_DATA(sequenceValue, columns);
				READ_DATA(sequenceValue, rows);
				READ_DATA(sequenceValue, start_frame);
				READ_DATA(sequenceValue, end_frame);

				std::string texture;
				READ_DATA(sequenceValue, texture);

				sequence.texture = __registry.Get<en::Texture>(texture, __renderer);

				_sequences[sequence.name] = sequence;
			}
		}

		std::string default_sequence;
		if (!READ_DATA(value, default_sequence))
		{
			default_sequence = _sequences.begin()->first;
		}

		setSequence(default_sequence);	

		return true;
	}

	void SpriteAnimComponent::setSequence(const std::string& name)
	{
		if (_sequence && _sequence->name == name) return;

		if (_sequences.find(name) != _sequences.end())
		{
			_sequence = &_sequences[name];

			frame = _sequence->start_frame;
			frameTime = 0;
		}
	}

	Rect& SpriteAnimComponent::_Source()
	{
		Vector2 cellSize = _sequence->texture->getSize() / Vector2{ _sequence->num_columns, _sequence->num_rows };
		int column = (frame - 1) % _sequence->num_columns;
		int row = (frame - 1) / _sequence->num_columns;

		source.x = (int) (column * cellSize.x);
		source.y = (int) (row * cellSize.y);
		source.w = (int) (cellSize.x);
		source.h = (int) (cellSize.y);

		return source;
	}
}