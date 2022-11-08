#include "CameraControllerComponent.h"
#include "Engine.h"

namespace en
{
	void CameraController::Update()
	{
		if (en::__inputsys.getKeyState(en::key_up) == en::InputSystem::KeyState::HELD) _owner->_transform.position.y += speed * en::__time.ci_time;

		if (en::__inputsys.getKeyState(en::key_down) == en::InputSystem::KeyState::HELD) _owner->_transform.position.y -= speed * en::__time.ci_time;

		if (en::__inputsys.getKeyState(en::key_right) == en::InputSystem::KeyState::HELD) _owner->_transform.position.x -= speed * en::__time.ci_time;

		if (en::__inputsys.getKeyState(en::key_left) == en::InputSystem::KeyState::HELD) _owner->_transform.position.x += speed * en::__time.ci_time;

		if (en::__inputsys.getKeyState(en::key_w) == en::InputSystem::KeyState::HELD) _owner->_transform.position.z += speed * speed * en::__time.ci_time;

		if (en::__inputsys.getKeyState(en::key_s) == en::InputSystem::KeyState::HELD) _owner->_transform.position.z -= speed * speed * en::__time.ci_time;
	}

	bool CameraController::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool CameraController::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, speed);

		return true;
	}
}