#ifndef _COMPONENT_LIGHT_H
#define _COMPONENT_LIGHT_H

#include "Framework/Component.h"

namespace en
{
	class LightComponent : public Component
	{
	public:
		CLONE(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 ambient { 0.0f };
		glm::vec3 diffuse { 1.0f };
		glm::vec3 specular { 1.0f };
	};
}

#endif // _COMPONENT_LIGHT_H