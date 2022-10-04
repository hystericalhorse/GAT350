#ifndef _RENDERER_H
#define _RENDERER_H

#include "Texture.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Matrix3x3.h"

struct SDL_Renderer; // Forward Declaration
struct SDL_Window; // Forward Declaration

namespace en
{
	struct Transform;
	struct Vector2;
	struct Color;
	struct Rect;
	struct Matrix3x3;

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

		void Init();
		void Shutdown();

		void Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle = 0, const Vector2& scale = Vector2{1, 1}, const Vector2& regist = Vector2{ .5, .5 });
		void Draw(std::shared_ptr<Texture> texture, const Transform& transform, const Vector2& regist = Vector2{ .5, .5 });
		void Draw(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& regist = Vector2{ .5, .5 }, bool flipH = false);
		void Draw2(std::shared_ptr<Texture> texture, const Rect& source, const Transform& transform, const Vector2& regist = Vector2{ .5, .5 }, bool flipH = false);

		void newWindow(const char* title, int width, int height);
		void beginFrame();
		void endFrame();
		void setClearColor(const Color& color) { _clearcolor = color; }
		Color& getClearColor() { return _clearcolor; }

		void drawLine(float x1, float y1, float x2, float y2, const Color& color);
		void drawLine(const Vector2& v1, const Vector2& v2, const Color& color);

		void drawPoint(float x, float y, const Color& color);
		void drawPoint(const Vector2& vector, const Color& color); // Pass by value

		void drawCircle(float x, float y, float radius, const Color& color);
		void drawCircle(Vector2& position, float radius, const Color& color);

		int get_window_width() { return width; }
		int get_window_height() { return height; }

		friend class Text;
		friend class Texture;

		SDL_Renderer* _renderer{ nullptr };
		SDL_Window* _window{ nullptr };

		Matrix3x3 _view;
		Matrix3x3 _viewport;

		void setView(const Matrix3x3& view) { _view = view; }
		void setViewport(const Matrix3x3& viewport) { _viewport = viewport; }

	private:
		int width = 0;
		int height = 0;

		Color _clearcolor{0, 0, 0, 255};
	};
}

#endif // _RENDERER_H