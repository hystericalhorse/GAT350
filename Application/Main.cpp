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

en::Vector3 colors1[] =
{
	{ 0.0f,  0.5f,  1.0f},
	{ 1.0f,  1.0f,  1.0f},
	{ 1.0f,  1.0f,  1.0f},
	{ 1.0f,  1.0f,  1.0f},
	{ 1.0f,  1.0f,  1.0f},
	{ 1.0f,  1.0f,  1.0f}
};

const char* vertex_shader =
"#version 430 core\n"
"in vec3 v_position;"
"in vec3 v_color;"
"out vec3 color"
"void main() {"
"  gl_Position = vec4(v_position, 1.0);"
"  color = v_color;"
"}";

const char* fragment_shader =
"#version 430 core\n"
"in vec3 color;"
"out vec4 f_color;"
"void main() {"
"	f_color = vec4(color, 1.0);"
"}";

int main(int argc, char** argv)
{
	en::flag_memory_debug();

	en::setPath("../assets");

	en::Engine::Instance().Init();

	en::__renderer.newWindow("Application", 800, 600);
	
	// OpenGL Vertex Buffer
	GLuint vbo_points = 0;
	glGenBuffers(1, &vbo_points);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points1, GL_STATIC_DRAW); // 36-Byte Buffer

	GLuint vbo_color = 0;
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(en::Vector3), colors1, GL_STATIC_DRAW);

	// OpenGL Vertex Array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_points);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Create OpenGL Shader

	std::shared_ptr<en::Shader> vs = en::__registry.Get<en::Shader>("shader/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<en::Shader> fs = en::__registry.Get<en::Shader>("shader/basic.frag", GL_FRAGMENT_SHADER);

	/**
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	**/


	// Create OpenGL Program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs->_shader);
	glAttachShader(program, vs->_shader);
	glLinkProgram(program);
	glUseProgram(program);

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		en::__renderer.beginFrame();

		// DRAW
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();

	return 0;
}