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
	en::__gui.Init(en::__renderer);

	// LOAD SCENE
	auto scene = en::__registry.Get<en::Scene>("scene/red_fox_in_cubemap.scene");

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();
		en::__gui.beginFrame(en::__renderer);

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		/*
		ImGui::Begin("Editor");

		ImGui::End();
		*/

		auto actor = scene->getActor("Object");
		if (actor)
		{
			//actor->_transform.rotation.y -= en::__time.ci_time * 15.0f;
		}

		auto light = scene->getActor("Light");
		if (light)
		{
			float speed = 4.0f;

			if (en::__inputsys.getKeyState(en::key_up) == en::InputSystem::KeyState::HELD) light->_transform.position.y += speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_down) == en::InputSystem::KeyState::HELD) light->_transform.position.y -= speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_right) == en::InputSystem::KeyState::HELD) light->_transform.position.x -= speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_left) == en::InputSystem::KeyState::HELD) light->_transform.position.x += speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_w) == en::InputSystem::KeyState::HELD) light->_transform.position.z += speed * speed * en::__time.ci_time;
			if (en::__inputsys.getKeyState(en::key_s) == en::InputSystem::KeyState::HELD) light->_transform.position.z -= speed * speed * en::__time.ci_time;
		}

		scene->Update();
		en::__renderer.beginFrame({ 0.0f, 0.0f, 0.0f, 1.0f});

		// DRAW
		scene->PreRender(en::__renderer);
		scene->Render(en::__renderer);
		en::__gui.Draw();

		en::__renderer.endFrame();
		en::__gui.endFrame();
	}

	scene->Remove();
	en::Engine::Instance().Shutdown();

	return 0;
}