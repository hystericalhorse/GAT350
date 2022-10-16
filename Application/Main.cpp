#include "Engine.h"
#include <iostream>

float points1[] =
{
	-0.5f, -0.5f,  0.0f,
	-0.5f,  0.5f,  0.0f,
	 0.5f, -0.5f,  0.0f,
	 0.5f,  0.5f,  0.0f,
	 0.5f, -0.5f,  0.0f,
	-0.5f,  0.5f,  0.0f
};

glm::vec3 colors1[] =
{
	{ 0.0f,  0.0f,  1.0f },
	{ 1.0f,  0.0f,  0.5f },
	{ 0.5f,  0.0f,  0.5f },
	{ 0.0f,  0.0f,  1.0f },
	{ 0.5f,  0.0f,  0.5f },
	{ 1.0f,  0.0f,  0.5f }
};

glm::vec2 uv1[] =
{
	{0.0, 0.0},
	{0.0, 1.0},
	{1.0, 0.0},
	{1.0, 1.0},
	{1.0, 0.0},
	{0.0, 1.0}
};

int main(int argc, char** argv)
{
	LOG("Application Start.");

	en::flag_memory_debug();

	en::setPath("../assets");

	en::Engine::Instance().Init();
	LOG("Engine Init...");

	en::__renderer.newWindow("Application", 800, 600);
	
	// OpenGL Vertex Buffer
	GLuint vbo_points = 0;
	glGenBuffers(1, &vbo_points);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points1, GL_STATIC_DRAW); // 36-Byte Buffer

	GLuint vbo_color = 0;
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors1, GL_STATIC_DRAW);

	GLuint vbo_uv = 0;
	glGenBuffers(1, &vbo_uv);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), uv1, GL_STATIC_DRAW);

	// OpenGL Vertex Array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// Create OpenGL Shader
	std::shared_ptr<en::Shader> vs = en::__registry.Get<en::Shader>("shader/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<en::Shader> fs = en::__registry.Get<en::Shader>("shader/basic.frag", GL_FRAGMENT_SHADER);

	// Create OpenGL Program
	std::shared_ptr<en::Program> program = en::__registry.Get<en::Program>("shader/basic.prog");
	program->Link();
	program->Use();

	// Create OpenGL Texture
	std::shared_ptr<en::Texture> texture = en::__registry.Get<en::Texture>("texture/crate.png");
	texture->Bind();

	// Modify Uniform Objects
	program->setUniform("scale", 1.0f);

	glm::mat4 mx{ 1.0 };
	program->setUniform("transform", mx);

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		// GL

		en::__renderer.beginFrame({0.0f, 0.0f, 0.0f, 1.0f});

		// DRAW
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();

	return 0;
}