#include "Material.h"
#include "Engine.h"

namespace en
{
	bool Material::Create(std::string name, ...)
	{
		rapidjson::Document document;
		bool success = en::json::Load(name, document);
		if (!success)
		{
			LOG("Could not load program at %s", name.c_str());
			return false;
		}

		std::string program;
		READ_DATA(document, program);

		_program = en::__registry.Get<en::Program>(program);

		std::string texture;
		READ_DATA(document, texture);
		if (!texture.empty())
		{
			_textures.push_back(en::__registry.Get<en::Texture>(texture));
		}

		READ_DATA(document, ambient);
		READ_DATA(document, diffuse);
		READ_DATA(document, specular);
		READ_DATA(document, shininess);

		return true;
	}

	void Material::Link()
	{
		_program->Link();
	}

	void Material::Bind()
	{
		_program->Use();

		for (auto& texture : _textures)
		{
			texture->Bind();
		}
	}
}