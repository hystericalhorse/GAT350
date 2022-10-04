#include "SpriteComponent.h"
#include "Engine.h"

namespace en
{
	void SpriteComponent::Update()
	{

	}

	void SpriteComponent::Draw(Renderer& renderer)
	{	
		renderer.Draw(_texture, _Source(), _owner->_Transform());
	}

	bool SpriteComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool SpriteComponent::Read(const rapidjson::Value& value)
	{
		std::string texture;
		Rect& source = this->_Source();
		
		READ_DATA(value, texture);
		_texture = en::__registry.Get<en::Texture>(texture, __renderer);

		if (!READ_DATA(value, source))
		{
			source.x = 0; source.y = 0;
			source.w = (int) _texture->getSize().x;
			source.h = (int) _texture->getSize().y;
		}

		return true;
	}
}