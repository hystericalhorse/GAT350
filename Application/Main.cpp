#include "Engine.h"
#include <iostream>

int main(int argc, char** argv)
{
	en::flag_memory_debug();

	en::Engine::Instance().Init();
	en::Engine::Instance().Register();

	en::__renderer.newWindow("Application", 800, 600);

	float angle = 0.0f;
	float val = 0.001f;
	en::Vector2 pos {0, 0};

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;
		if (en::__inputsys.getKeyState(en::key_left) == en::InputSystem::KeyState::HELD) pos.x -= en::__time.ci_time * 2;
		if (en::__inputsys.getKeyState(en::key_right) == en::InputSystem::KeyState::HELD) pos.x += en::__time.ci_time * 2;

		float rrr = en::randomf(0.0, 1.0);
		float ggg = en::randomf(0.0, 1.0);
		float bbb = en::randomf(0.0, 1.0);
		en::__renderer.beginFrame({ 0.0f, 0.0f, 0.0f, 1.0f });

		angle += 180.0f * en::__time.ci_time;

		glPushMatrix();

		// val += 0.001f;
		glScalef(0.999 - val, 0.999 - val, 0.999 - val);
		glRotatef(angle, 1, 0, 0);
		glTranslatef(pos.x, pos.y, 0);

		glBegin(GL_TRIANGLES);

		glColor3f(0.1f, 0.0f, 0.0f);
		glVertex2f(0.8f, 0.8f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(0.0f, -0.8f);
		glColor3f(0.0f, 0.0f, 0.1f);
		glVertex2f(-0.8f, 0.8f);

		glEnd();

		glPopMatrix();

		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();

	return 0;
}