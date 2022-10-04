#include "Engine.h"
#include <iostream>

int main(int argc, char** argv)
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

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();

		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();

	return 0;
}