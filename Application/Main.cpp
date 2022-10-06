#include "Engine.h"
#include <iostream>

int main(int argc, char** argv)
{
	en::flag_memory_debug();

	en::Engine::Instance().Init();
	en::Engine::Instance().Register();

	en::__renderer.newWindow("Application", 800, 600);

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		en::__renderer.beginFrame({ 0.0f, 0.0f, 0.0f, 1.0f });

		// DRAW
		
		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();

	return 0;
}