#include "Engine.h"
#include <iostream>

int main(int argc, char** argv)
{
	LOG("Application Start.");

	en::flag_memory_debug();

	en::setPath("../assets");

	en::Engine::Instance().Init();
	LOG("Engine Init...");

	en::__renderer.newWindow("Application", 800, 600);

	// LOAD SCENE
	auto scene = en::__registry.Get<en::Scene>("scene/lights_normal.scene");

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		scene->Update();

		auto actor = scene->getActor("Object");
		if (actor)
		{
			//actor->_transform.rotation.y -= en::__time.ci_time * 15.0f;
		}

		auto light = scene->getActor("Light");
		if (light)
		{
			float speed = 4.0;
			//light->_transform.position.x = std::sin(en::__time.time) * 0.1;

			if (en::__inputsys.getKeyState(en::key_up) == en::InputSystem::KeyState::HELD) light->_transform.position.y += speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_down) == en::InputSystem::KeyState::HELD) light->_transform.position.y -= speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_right) == en::InputSystem::KeyState::HELD) light->_transform.position.x -= speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_left) == en::InputSystem::KeyState::HELD) light->_transform.position.x += speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_w) == en::InputSystem::KeyState::HELD) light->_transform.position.z += speed * speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_s) == en::InputSystem::KeyState::HELD) light->_transform.position.z -= speed * speed * en::__time.ci_time;
			
		}

		en::__renderer.beginFrame({ 0.0f, 0.0f, 0.0f, 1.0f});

		// DRAW
		scene->Draw(en::__renderer);

		en::__renderer.endFrame();
	}

	scene->Remove();
	en::Engine::Instance().Shutdown();

	return 0;
}