#include "CameraComponent.h"
#include "Engine.h"

namespace en
{
	void CameraComponent::Init()
	{
		setViewport(_viewportsize);
	}

	void CameraComponent::Update()
	{
		Matrix3x3 mxT = Matrix3x3::translate(-_owner->_Transform().position);
		Matrix3x3 mxR = Matrix3x3::rotate(-en::radians(_owner->_Transform().rotation));

		_view = mxT * mxR;

		__renderer.setView(_view);
	}

	void CameraComponent::setViewport(const Vector2& size)
	{
		Matrix3x3 mxT = Matrix3x3::translate(size * 0.5f);

		_viewport = mxT;
		__renderer.setViewport(_viewport);
	}

	bool CameraComponent::Write(const rapidjson::Value& value) const
	{
		// TODO

		return true;
	}

	bool CameraComponent::Read(const rapidjson::Value& value)
	{
		Vector2& viewport_size = _viewportsize;

		READ_DATA(value, viewport_size);

		return true;
	}


}
