#ifndef _GUI_H
#define _GUI_H
#include "Renderer.h"
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>

namespace en
{
	class GUI
	{
	public:
		GUI() = default;
		~GUI() = default;

		void Init(Renderer& renderer);
		void Shutdown();

		void beginFrame(Renderer& renderer);
		void endFrame();
		void Draw();

		void Update(SDL_Event& event);
	};
}

#endif // _GUI_H
