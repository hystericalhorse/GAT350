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
			// material->uv_offset.x += en::__time.ci_time * 1;
		}

		scene->Update();

		auto actor = scene->getActor("Object");
		if (actor)
		{
			// actor->_transform.rotation.y += en::__time.ci_time * 45.0f;
		}

		en::__renderer.beginFrame({ 0.8f, 0.8f, 0.8f, 1.0f});

		// DRAW
		scene->Draw(en::__renderer);

		en::__renderer.endFrame();
	}

	scene->Remove();
	en::Engine::Instance().Shutdown();

	return 0;
}