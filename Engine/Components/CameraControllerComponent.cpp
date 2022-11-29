#include "CameraControllerComponent.h"
#include "Engine.h"

namespace en
{
	void CameraController::Init()
	{
		glm::vec3 v = en::QuaternionToEuler(_owner->_transform.rotation);

		_pitch = v.x;
		_yaw = v.y;
	}

	void CameraController::Update()
	{
		if (__inputsys.getButtonState(btn_right) == InputSystem::KeyState::HELD)
		{
			glm::vec2 axis = __inputsys.getMouseRelative() * sensitivity;

			_yaw += axis.x;
			_pitch -= axis.y;
			//std::cout << _pitch << std::endl;
			_pitch = glm::clamp(_pitch, -89.0f, 89.0f);
		}

		glm::vec3 forward;
		forward.x = cos(glm::radians(_yaw - 90.0f)) * cos(glm::radians(_pitch));
		forward.y = sin(glm::radians(_pitch));
		forward.z = sin(glm::radians(_yaw - 90.0f)) * cos(glm::radians(_pitch));
		forward = glm::normalize(forward);

		glm::mat4 view = glm::lookAt(glm::vec3{ 0.0f }, -forward, glm::vec3{ 0, 1, 0 });
		_owner->_transform.rotation = glm::conjugate(glm::quat_cast(view));

		glm::vec3 direction{ 0 };

		if (__inputsys.getKeyState(key_a) == InputSystem::KeyState::HELD)		direction.x += 1;
		if (__inputsys.getKeyState(key_d) == InputSystem::KeyState::HELD)		direction.x -= 1;

		if (__inputsys.getKeyState(key_space) == InputSystem::KeyState::HELD)	direction.y += 1;
		if (__inputsys.getKeyState(key_lctrl) == InputSystem::KeyState::HELD)	direction.y -= 1;

		if (__inputsys.getKeyState(key_w) == InputSystem::KeyState::HELD)		direction.z += 1;
		if (__inputsys.getKeyState(key_s) == InputSystem::KeyState::HELD)		direction.z -= 1;

		direction = _owner->_transform.rotation * direction;

		if (en::__inputsys.getKeyState(en::key_lshift) == en::InputSystem::KeyState::HELD)
		{
			_owner->_transform.position += direction * (doublespeed * __time.ci_time);
		}
		else
		{
			_owner->_transform.position += direction * (speed * __time.ci_time);
		}

		

		/*
		if (en::__inputsys.getKeyState(en::key_up) == en::InputSystem::KeyState::HELD) _owner->_transform.position.y += speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_down) == en::InputSystem::KeyState::HELD) _owner->_transform.position.y -= speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_right) == en::InputSystem::KeyState::HELD) _owner->_transform.position.x -= speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_left) == en::InputSystem::KeyState::HELD) _owner->_transform.position.x += speed * en::__time.ci_time;

		if (en::__inputsys.getKeyState(en::key_w) == en::InputSystem::KeyState::HELD) _owner->_transform.position.z += speed * speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_s) == en::InputSystem::KeyState::HELD) _owner->_transform.position.z -= speed * speed * en::__time.ci_time;
		*/
	}

	bool CameraController::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraController::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);
		doublespeed = speed * 2;
		READ_DATA(value, sensitivity);

		return true;
	}
}