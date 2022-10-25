#include "Engine.h"
#include <iostream>

float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};

int main(int argc, char** argv)
{
	LOG("Application Start.");

	en::flag_memory_debug();

	en::setPath("../assets");

	en::Engine::Instance().Init();
	LOG("Engine Init...");

	en::__renderer.newWindow("Application", 800, 600);

	// LOAD SCENE
	auto scene = std::make_unique<en::Scene>();

	rapidjson::Document document;
	bool success = en::json::Load("scene/basic.scene", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "scene/basic.scene");
	}
	else
	{
		scene->Read(document);
		scene->Init();
	}


	glm::mat4 model{ 1.0 };

	float pitch = 0.0f;
	float roll = 0.0f;
	float yaw = 0.0f;

	glm::mat4 projection = glm::perspective(45.0f, (float) en::__renderer.get_window_width() / en::__renderer.get_window_height(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 6 };
	float speed = 2;
	float camRot = 0.0f;

	std::vector<en::Transform> transforms;
	int ii = 1;
	for (int i = 0; i < ii; i++)
	{
		transforms.push_back(
			{
				{ en::randomf(-5.0f, 5.0f), en::randomf(-5.0f, 5.0f), en::randomf(-5.0f, 5.0f)},
				{ en::randomf(-180.0f, 180.0f), en::randomf(-180.0f, 180.0f), en::randomf(-180.0f, 180.0f) }
			});
	}

	// Create Object (Creates Program, Shaders, and Textures)
	auto m = en::__registry.Get<en::Model>("model/ogre.obj");
	std::shared_ptr<en::Material> material = en::__registry.Get<en::Material>("material/ogre.mtrl");
	material->Bind();

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;
		
		scene->Update();

		/*
		if (en::__inputsys.getKeyState(en::key_up) == en::InputSystem::KeyState::HELD) cameraPosition.y += speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_down) == en::InputSystem::KeyState::HELD) cameraPosition.y -= speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_right) == en::InputSystem::KeyState::HELD) cameraPosition.x += speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_left) == en::InputSystem::KeyState::HELD) cameraPosition.x -= speed * en::__time.ci_time;
		
		if (en::__inputsys.getKeyState(en::key_w) == en::InputSystem::KeyState::HELD) cameraPosition.z -= speed * en::__time.ci_time * 5;
		if (en::__inputsys.getKeyState(en::key_s) == en::InputSystem::KeyState::HELD) cameraPosition.z += speed * en::__time.ci_time * 5;
		if (en::__inputsys.getKeyState(en::key_a) == en::InputSystem::KeyState::HELD) camRot -= speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_d) == en::InputSystem::KeyState::HELD) camRot += speed * en::__time.ci_time;
		*/

		en::__renderer.beginFrame({0.0f, 0.0f, 0.0f, 1.0f});

		// DRAW
		scene->Draw(en::__renderer);

		/*
		for (size_t i = 0; i < transforms.size(); i++)
		{
			// GL
			// model = glm::eulerAngleXYZ(pitch, yaw, roll);

			transforms[i].rotation += glm::vec3 { (5 * speed * en::__time.ci_time), (5 * speed * en::__time.ci_time), (5 * speed * en::__time.ci_time) };
			glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
			glm::mat4 mvp = projection * view * (glm::mat4) transforms[i];

			// model view position matrix
			material->getProgram()->setUniform("mvp", mvp);

			m->_vertexBuffer.Draw();
		}
		*/

		en::__renderer.endFrame();
	}

	scene->Remove();
	en::Engine::Instance().Shutdown();

	return 0;
}