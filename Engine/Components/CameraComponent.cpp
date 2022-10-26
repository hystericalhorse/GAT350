#include "CameraComponent.h"
#include "Engine.h"

namespace en
{
	void CameraComponent::Init()
	{
		
	}

	void CameraComponent::Update()
	{
		_view = glm::lookAt(_owner->_transform.position, _owner->_transform.position + _owner->_transform.forward(), glm::vec3{ 0, 1, 0 });
	}

	void CameraComponent::setPerspective(float fov, float aspect, float near, float far)
	{
		_projection = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	bool CameraComponent::Write(const rapidjson::Value& value) const
	{
		// TODO

		return true;
	}

	bool CameraComponent::Read(const rapidjson::Value& value)
	{
		float fov;
		READ_DATA(value, fov);

		float aspect_ratio;
		if (!READ_DATA(value, aspect_ratio))
		{
			aspect_ratio = __renderer.get_window_width() / (float)__renderer.get_window_height();
		}

		float near;
		float far;

		READ_DATA(value, near);
		READ_DATA(value, far);

		setPerspective(fov, aspect_ratio, near, far);

		return true;
	}


}
