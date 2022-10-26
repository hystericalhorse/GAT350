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
			program->setUniform("l_ambient", ambient);
			program->setUniform("l_diffuse", diffuse);
			program->setUniform("l_specular", specular);
			program->setUniform("l_position", position);
		}
	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, ambient);
		READ_DATA(value, diffuse);
		READ_DATA(value, specular);

		return true;
	}

}