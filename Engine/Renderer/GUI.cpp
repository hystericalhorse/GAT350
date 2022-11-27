#include "GUI.h"

namespace en
{
	void GUI::Init(Renderer& renderer)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		ImGui_ImplSDL2_InitForOpenGL(renderer._window, renderer._context);
		const char* glsl_version = "#version 430";
		ImGui_ImplOpenGL3_Init(glsl_version);

		ImGui::StyleColorsDark();
	}

	void GUI::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void GUI::beginFrame(Renderer& renderer)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		//ImGui_ImplSDL2_NewFrame(renderer.m_window);
		ImGui::NewFrame();
	}

	void GUI::endFrame()
	{
		ImGui::EndFrame();
	}

	void GUI::Draw()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void GUI::Update(SDL_Event& event)
	{
		ImGui_ImplSDL2_ProcessEvent(&event);
	}
}