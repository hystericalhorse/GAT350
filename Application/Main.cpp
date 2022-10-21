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

	std::shared_ptr<en::VertexBuffer> vb = en::__registry.Get<en::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0); // position
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float)); // color
	vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float)); // uv

	// Create Object (Creates Program, Shaders, and Textures)
	std::shared_ptr<en::Material> material = en::__registry.Get<en::Material>("material/box.mtrl");
	material->Link();
	material->Bind();

	glm::mat4 model{ 1.0 };

	float pitch = 0.0f;
	float roll = 0.0f;
	float yaw = 0.0f;

	glm::mat4 projection = glm::perspective(45.0f, (float) en::__renderer.get_window_width() / en::__renderer.get_window_height(), 0.01f, 100.0f);

	glm::vec3 cameraPosition = glm::vec3{ 0, 0, 3 };
	float speed = 2;
	float camRot = 0.0f;

	std::vector<en::Transform> transforms;
	int ii = 1000;
	for (int i = 0; i < ii; i++)
	{
		transforms.push_back(
			{
				{ en::randomf(-20.0f, 20.0f), en::randomf(-20.0f, 20.0f), en::randomf(-20.0f, 20.0f)},
				{ en::randomf(-180.0f, 180.0f), en::randomf(-180.0f, 180.0f), en::randomf(-180.0f, 180.0f) }
			});
	} 

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;
		
		if (en::__inputsys.getKeyState(en::key_up) == en::InputSystem::KeyState::HELD) cameraPosition.y += speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_down) == en::InputSystem::KeyState::HELD) cameraPosition.y -= speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_right) == en::InputSystem::KeyState::HELD) cameraPosition.x += speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_left) == en::InputSystem::KeyState::HELD) cameraPosition.x -= speed * en::__time.ci_time;
		
		if (en::__inputsys.getKeyState(en::key_w) == en::InputSystem::KeyState::HELD) cameraPosition.z -= speed * en::__time.ci_time * 5;
		if (en::__inputsys.getKeyState(en::key_s) == en::InputSystem::KeyState::HELD) cameraPosition.z += speed * en::__time.ci_time * 5;
		if (en::__inputsys.getKeyState(en::key_a) == en::InputSystem::KeyState::HELD) camRot -= speed * en::__time.ci_time;
		if (en::__inputsys.getKeyState(en::key_d) == en::InputSystem::KeyState::HELD) camRot += speed * en::__time.ci_time;

		en::__renderer.beginFrame({ 0.553, 0.584, 0.631, 1.0f });

		// DRAW
		for (size_t i = 0; i < transforms.size(); i++)
		{
			// GL
			// model = glm::eulerAngleXYZ(pitch, yaw, roll);

			transforms[i].rotation += glm::vec3 { (5 * speed * en::__time.ci_time), (5 * speed * en::__time.ci_time), (5 * speed * en::__time.ci_time) };
			glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
			glm::mat4 mvp = projection * view * (glm::mat4) transforms[i];

			// model view position matrix
			material->getProgram()->setUniform("mvp", mvp);
			
			vb->Draw();
		}


		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();

	return 0;
}