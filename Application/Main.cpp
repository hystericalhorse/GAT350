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
	auto scene = en::__registry.Get<en::Scene>("scene/lights_normal.scene");

	glm::vec3 rot{ 0, 0, 0 };

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();
		en::__gui.beginFrame(en::__renderer);

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		ImGui::Begin("Editor");
		ImGui::SliderFloat3("Rotation", &rot[0], -360.0f, 360.0f);
		ImGui::End();

		auto actor = scene->getActor("Object");
		if (actor)
		{
			if (en::__inputsys.getKeyState(en::key_a) == en::InputSystem::KeyState::HELD) ;
			if (en::__inputsys.getKeyState(en::key_d) == en::InputSystem::KeyState::HELD) ;

			actor->_transform.rotation = en::EulerToQuaternion(rot);
		}

		auto light = scene->getActor("Light");
		auto camera = scene->getActor("Camera");
		if (light && camera)
		{
			//light->_transform.position	= camera->_transform.position;
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