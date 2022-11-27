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

		std::string cubemap;
		READ_DATA(document, cubemap);
		if (!cubemap.empty())
		{
			std::string cubemap_extension;
			READ_DATA(document, cubemap_extension);

			_textures.push_back(en::__registry.Get<en::CubemapTexture>(cubemap, cubemap_extension));
		}

		std::vector<std::string> textures;
		READ_DATA(document, textures);
		for (auto& texture : textures)
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

		for (size_t i = 0; i < _textures.size(); i++)
		{
			if (i > 31)
			{
				LOG("ERROR: OPENGL DOES NOT SUPPORT MORE THAN 31 CONCURRENT TEXTURES.");
				return;
			}
			_textures[i]->Activate(GL_TEXTURE0 + (int) i);
			_textures[i]->Bind();
		}
	}
}