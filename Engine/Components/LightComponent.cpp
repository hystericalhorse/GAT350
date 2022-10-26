#include "LightComponent.h"
#include "Engine.h"

namespace en
{
	void LightComponent::Update()
	{
		glm::vec4 position = __renderer.getView() * glm::vec4(_owner->_transform.position, 1);

		auto programs = __registry.Get<en::Program>();

		for (auto& program : programs)
		{
			program->Use();

			program->setUniform("l_color", color);
			program->setUniform("l_position", position);
		}
	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, color);

		return true;
	}

}