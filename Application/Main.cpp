#include "Engine.h"
#include <iostream>

int main()
{
	en::Engine::Instance().Init();
	en::Engine::Instance().Register();

	en::__renderer.newWindow("Application", 800, 600);

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		en::__renderer.beginFrame();
		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();
}