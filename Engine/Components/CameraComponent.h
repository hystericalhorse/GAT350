#ifndef _COMPONENT_CAMERA_H
#define _COMPONENT_CAMERA_H

#include "Framework/Component.h"
#include "Math/Matrix3x3.h"
#include "Math/Vector2.h"

namespace en
{

	class CameraComponent : public Component
	{
	public:
		CLONE(CameraComponent);

		virtual void Init() override;
		virtual void Update() override;

		void setPerspective(float fov, float aspect, float near, float far);

		const glm::mat4& getView() { return _view; }
		const glm::mat4& getProjection() { return _projection; }


		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Vector2 _viewportsize;

		glm::mat4 _view { 1.0f };
		glm::mat4 _projection { 1.0f };
	};
}

#endif // _COMPONENT_CAMERA_H