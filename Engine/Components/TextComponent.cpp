#include "TextComponent.h"

#include "Engine.h"

namespace en
{
	void TextComponent::Update()
	{
		// TODO
	}

	void TextComponent::Draw(Renderer& renderer)
	{
		__renderer.Draw(_texture, _owner->_Transform(), registration);
	}

	void TextComponent::setText(const std::string& text)
	{
		_texture->CreateFromSurface(_font->CreateSurface(text, color), __renderer);
	}

	bool TextComponent::Write(const rapidjson::Value& value) const
	{
		// TODO

		return true;
	}

	bool TextComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, text);
		READ_DATA(value, font_name);
		READ_DATA(value, fontSize);
		READ_DATA(value, registration);
		READ_DATA(value, color);

		_font = __registry.Get<en::Font>(font_name, fontSize);
		_texture = std::make_unique<en::Texture>();

		setText(text);

		return true;
	}
}