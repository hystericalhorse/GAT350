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
	auto scene = en::__registry.Get<en::Scene>("scene/texture.scene");

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;
		
		auto material = en::__registry.Get<en::Material>("material/multi.mtrl");
		if (material)
		{
			
		}

		scene->Update();

		auto actor = scene->getActor("Object");
		if (actor)
		{
			actor->_transform.rotation.y -= en::__time.ci_time * 15.0f;
		}

		auto light = scene->getActor("Light");
		if (light)
		{
			//light->_transform.position.x = std::sin(en::__time.time);
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