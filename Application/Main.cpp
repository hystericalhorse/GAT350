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

const char* vertex_shader =
"#version 430 core\n"
"in vec3 position;"
"void main() {"
"  gl_Position = vec4(position, 1.0);"
"}";

const char* fragment_shader =
"#version 430 core\n"
"out vec4 color;"
"void main() {"
"	color = vec4(0.0f, 0.5f, 1.0f, 1.0f);"
"}";

int main(int argc, char** argv)
{
	en::flag_memory_debug();

	//en::setPath("../assets");

	en::Engine::Instance().Init();

	en::__renderer.newWindow("Application", 800, 600);
	
	// OpenGL Vertex Buffer
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points1, GL_STATIC_DRAW); // 36-Byte Buffer

	// OpenGL Vertex Array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// Create OpenGL Shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	// Create OpenGL Program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);
	glUseProgram(program);

	bool quit = false;
	while (!quit)
	{
		en::Engine::Instance().Update();

		if (en::__inputsys.getKeyState(en::key_escape) == en::InputSystem::KeyState::PRESSED) quit = true;

		en::__renderer.beginFrame({ 0.5f, 0.25f, 0.5f, 1.0f });

		// DRAW
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		en::__renderer.endFrame();
	}

	en::Engine::Instance().Shutdown();

	return 0;
}