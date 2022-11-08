#include "LightComponent.h"
#include "Engine.h"

#include "Core/Utils.h"

namespace en
{
	void LightComponent::Update()
	{
		glm::vec4 position = __renderer.getView() * glm::vec4(_owner->_transform.position, 1);

		glm::vec direction = _owner->_transform.forward();

		auto programs = __registry.Get<en::Program>();

		for (auto& program : programs)
		{
			program->Use();
			program->setUniform("l_type", (int) type);

			program->setUniform("l_ambient", ambient);
			program->setUniform("l_color", color);
			program->setUniform("l_position", position);

			program->setUniform("l_direction", direction);
			program->setUniform("l_cutoff", glm::radians(cutoff));
			program->setUniform("l_exponent", exponent);
		}

		
	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, color);
		READ_DATA(value, ambient);

		std::string type_name;
		READ_DATA(value, type_name);
		if (en::Utils::compare_strings(type_name, "directional"))
		{
			type = Type::Directional;
		}
		else if (en::Utils::compare_strings(type_name, "spot") || en::Utils::compare_strings(type_name, "spotlight"))
		{
			type = Type::Spot;
		}
		else
		{
			type = Type::Point;
		}

		READ_DATA(value, cutoff);
		READ_DATA(value, exponent);

		return true;
	}

}