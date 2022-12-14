#ifndef _COMPONENT_CAMERA_CONTROLLER_H
#define _COMPONENT_CAMERA_CONTROLLER_H

#include "Framework/Component.h"

namespace en
{
	class CameraController : public Component
	{
	public:
		CLONE(CameraController);

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:

		float speed = 0.0f;
	};
}

#endif // _COMPONENT_CAMERA_CONTROLLER_H