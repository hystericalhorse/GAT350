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

		READ_DATA(document, color);
		READ_DATA(document, shininess);

		glm::vec2& tiling = uv_tiling;
		glm::vec2& offset = uv_offset;

		READ_DATA(document, tiling);
		READ_DATA(document, offset);

		return true;
	}

	void Material::Bind()
	{
		_program->Use();

		_program->setUniform("m_color", color);
		_program->setUniform("m_shininess", shininess);

		_program->setUniform("m_tiling", uv_tiling);
		_program->setUniform("m_offset", uv_offset);

		for (auto& texture : _textures)
		{
			texture->Bind();
		}
	}
}