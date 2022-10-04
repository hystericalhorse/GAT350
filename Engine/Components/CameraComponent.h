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

		const Matrix3x3& _View() { return _view; }

		void setViewport(const Vector2& size);
		const Matrix3x3& _Viewport() { return _viewport; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		Vector2 _viewportsize;

		Matrix3x3 _view;
		Matrix3x3 _viewport;
	};
}

#endif // _COMPONENT_CAMERA_H