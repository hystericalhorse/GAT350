#include "LightComponent.h"
#include "Engine.h"

#include "Core/Utils.h"

namespace en
{
	void LightComponent::Update()
	{
		
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

	void LightComponent::setProgram(std::shared_ptr<en::Program> program, int index)
	{
		glm::vec4 position = __renderer.getView() * glm::vec4(_owner->_transform.position, 1.0);
		glm::vec3 direction = _owner->_transform.forward();

		std::string lightname = "lights[" + std::to_string(index) + "]";

		program->Use();
		program->setUniform(lightname + ".type", (int) type);
		program->setUniform(lightname + ".color", (glm::vec3) color);
		program->setUniform(lightname + ".position", (glm::vec4) position);
		program->setUniform(lightname + ".direction", (glm::vec3) direction);
		program->setUniform(lightname + ".cutoff", (float) cutoff);
		program->setUniform(lightname + ".exponent", (float) exponent);
	}

}