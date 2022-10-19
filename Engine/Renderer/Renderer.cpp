#include "Renderer.h"
#include "Core/Logger.h"
#include "Math/Transform.h"
#include "Math/Rect.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>
#include <SDL_image.h>

namespace en
{
	void Renderer::Init()
	{
		SDL_Init(SDL_INIT_VIDEO);

		TTF_Init();

		_view = Matrix3x3::identity;
		_viewport = Matrix3x3::identity;
	}

	void Renderer::Shutdown()
	{
		SDL_GL_DeleteContext(_context);
		SDL_DestroyWindow(_window);

		TTF_Quit();
		IMG_Quit();
	}

	void Renderer::newWindow(const char* title, int width, int height, bool fullscreen)
	{
		this->width = width;
		this->height = height;
		int flags = (fullscreen) ? SDL_WINDOW_FULLSCREEN : (SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		_window = SDL_CreateWindow(title, 100, 100, width, height, SDL_WINDOW_OPENGL | flags);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetSwapInterval(1);

		_context = SDL_GL_CreateContext(_window);
		gladLoadGL();

		glViewport(0, 0, width, height);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void Renderer::beginFrame()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::beginFrame(const RenderColor& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::endFrame()
	{
		SDL_GL_SwapWindow(_window);
	}

	void Renderer::drawLine(float x1, float y1, float x2, float y2, const Color& color)
	{
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(_renderer, x1, y1, x2, y2);
	}

	void Renderer::drawLine(const Vector2& v1, const Vector2& v2, const Color& color)
	{
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(_renderer, v1.x, v1.y, v2.x, v2.y);
	}

	void Renderer::drawPoint(float x, float y, const Color& color)
	{
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(_renderer, x, y);
	}

	void Renderer::drawPoint(const Vector2& vector, const Color& color)
	{
		SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(_renderer, vector.x, vector.y);
	}

	void Renderer::drawCircle(float x_pos, float y_pos, float radius, const Color& color)
	{
		const int32_t diameter = (int32_t) (radius * 2);

		float x = (radius - 1);
		float y = 0;
		float tx = 1;
		int8_t ty = 1;
		int32_t error = (int32_t) (tx - diameter);

		while (x >= y)
		{
			//  each of the following renders an octant of the circle
			drawPoint(x_pos + x, y_pos - y, color);
			drawPoint(x_pos + x, y_pos + y, color);
			drawPoint(x_pos - x, y_pos - y, color);
			drawPoint(x_pos - x, y_pos + y, color);
			drawPoint(x_pos + y, y_pos - x, color);
			drawPoint(x_pos + y, y_pos + x, color);
			drawPoint(x_pos - y, y_pos - x, color);
			drawPoint(x_pos - y, y_pos + x, color);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (int32_t) (tx - diameter);
			}
		}
	}

	void Renderer::drawCircle(Vector2& position, float radius, const Color& color)
	{
		const int32_t diameter = (int32_t) (radius * 2);

		float x_pos = position.x;
		float y_pos = position.y;

		float x = (radius - 1);
		float y = 0;
		float tx = 1;
		int8_t ty = 1;
		int32_t error = (int32_t) (tx - diameter);

		while (x >= y)
		{
			//  each of the following renders an octant of the circle
			drawPoint(x_pos + x, y_pos - y, color);
			drawPoint(x_pos + x, y_pos + y, color);
			drawPoint(x_pos - x, y_pos - y, color);
			drawPoint(x_pos - x, y_pos + y, color);
			drawPoint(x_pos + y, y_pos - x, color);
			drawPoint(x_pos + y, y_pos + x, color);
			drawPoint(x_pos - y, y_pos - x, color);
			drawPoint(x_pos - y, y_pos + x, color);

			if (error <= 0)
			{
				++y;
				error += ty;
				ty += 2;
			}

			if (error > 0)
			{
				--x;
				tx += 2;
				error += (int32_t) (tx - diameter);
			}
		}
	}

	/** Deprecated *******************************
	* void Renderer::Draw(std::shared_ptr<en::Texture> texture, const Vector2& position, float angle, const Vector2& scale, const Vector2& regist)
	{
		Vector2 size = texture->getSize();
		size = size * scale;

		Vector2 origin = size * regist;
		Vector2 pos = position - origin;
		const SDL_Point center {(int) origin.x, (int) origin.y};

		SDL_Rect dest;
		// Destination Position
		dest.x = (int) pos.x;
		dest.y = (int) pos.y;
		// Scale
		dest.w = (int) size.x;
		dest.h = (int) size.y;

		// SDL_RenderCopyEx(_renderer, texture -> _texture, nullptr, &dest, angle, &center, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& regist)
	{
		Vector2 size = texture->getSize();
		size = size * transform.scale;

		Vector2 origin = size * regist;
		Vector2 pos = transform.position - origin;
		const SDL_Point center{ (int) origin.x, (int) origin.y };

		SDL_Rect dest;
		// Destination Position
		dest.x = (int)pos.x;
		dest.y = (int)pos.y;
		// Scale
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		// SDL_RenderCopyEx(_renderer, texture->_texture, nullptr, &dest, transform.rotation, &center, SDL_FLIP_NONE);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& regist, bool flipH)
	{
		Matrix3x3 mx = _viewport * _view * transform.matrix;

		Vector2 size { source.w, source.h };
		size *= mx.get_scale();

		Vector2 origin = size * regist;
		Vector2 pos = mx.get_translation() - origin;
		const SDL_Point center{ (int)origin.x, (int)origin.y };

		SDL_Rect src;
		src.x = source.x;
		src.y = source.y;
		src.w = source.w;
		src.h = source.h;

		SDL_Rect dest;
		// Destination Position
		dest.x = (int)pos.x;
		dest.y = (int)pos.y;
		// Scale
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_RendererFlip sdl_flip = (flipH) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

		// SDL_RenderCopyEx(_renderer, texture->_texture, &src, &dest, en::degrees(mx.get_rotation()), &center, sdl_flip);
	}

	void Renderer::Draw2(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& regist, bool flipH)
	{
		Vector2 size{ source.w, source.h };
		size *= transform.scale;

		Vector2 origin = size * regist;
		Vector2 pos = transform.position - origin;
		const SDL_Point center{ (int) origin.x, (int) origin.y };

		SDL_Rect src;
		src.x = source.x;
		src.y = source.y;
		src.w = source.w;
		src.h = source.h;

		SDL_Rect dest;
		// Destination Position
		dest.x = (int)pos.x;
		dest.y = (int)pos.y;
		// Scale
		dest.w = (int)size.x;
		dest.h = (int)size.y;

		SDL_RendererFlip sdl_flip = (flipH) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

		// SDL_RenderCopyEx(_renderer, texture->_texture, &src, &dest, transform.rotation, &center, sdl_flip);
	}

	***************************************/
}