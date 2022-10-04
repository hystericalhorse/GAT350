#include "Renderer.h"
#include "Core/Logger.h"
#include "Math/Transform.h"
#include "Math/Rect.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include <iostream>

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
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);

		TTF_Quit();
	}

	void Renderer::Draw(std::shared_ptr<en::Texture> texture, const Vector2& position, float angle, const Vector2& scale, const Vector2& regist)
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

		SDL_RenderCopyEx(_renderer, texture -> _texture, nullptr, &dest, angle, &center, SDL_FLIP_NONE);
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

		SDL_RenderCopyEx(_renderer, texture->_texture, nullptr, &dest, transform.rotation, &center, SDL_FLIP_NONE);
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

		SDL_RenderCopyEx(_renderer, texture->_texture, &src, &dest, en::degrees(mx.get_rotation()), &center, sdl_flip);
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

		SDL_RenderCopyEx(_renderer, texture->_texture, &src, &dest, transform.rotation, &center, sdl_flip);
	}

	void Renderer::newWindow(const char* title, int width, int height)
	{
		this->width = width;
		this->height = height;

		_window = SDL_CreateWindow(title, 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}

	void Renderer::beginFrame()
	{
		SDL_SetRenderDrawColor(_renderer, _clearcolor.r, _clearcolor.g, _clearcolor.b, _clearcolor.a);
		SDL_RenderClear(_renderer);
	}

	void Renderer::endFrame()
	{
		SDL_RenderPresent(_renderer);
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
}