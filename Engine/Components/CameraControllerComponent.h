#ifndef _COMPONENT_CAMERA_CONTROLLER_H
#define _COMPONENT_CAMERA_CONTROLLER_H

#include "Framework/Component.h"

namespace en
{
	class CameraController : public Component
	{
	public:
		CLONE(CameraController);

		void Init() override;
		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		float& get_speed() { return this->speed; }

	private:

		float speed = 0.0f;
		float doublespeed = 0.0f;

		float _yaw = 0.0f; // Left/Right
		float _pitch = 0.0f; // Up/Down

		float sensitivity = 1.0f;
	};
}

#endif // _COMPONENT_CAMERA_CONTROLLER_H