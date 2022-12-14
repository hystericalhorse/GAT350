#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "Math/Vector2.h"
#include "Resource/Resource.h"
#include "Renderer.h"
#include <string>

struct SDL_Texture;
struct SDL_Surface;

namespace en
{
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		/** Deprecated **********************

		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		************************************/

		bool Load(const std::string& filename);
		bool Create(std::string filename, ...) override;

		static GLenum getInternalFormat(GLuint format);

		void Activate(GLuint unit) { glActiveTexture(unit); }
		void Bind() { glBindTexture(_target, _texture); }

		Vector2 getSize() const;

		friend class Renderer;
		friend class Component;

	protected:
		GLuint _texture = 0;
		GLenum _target = GL_TEXTURE_2D;

		void flipSurface(SDL_Surface* surface);

		/** Deprecated **********************
		
		SDL_Texture* _texture = nullptr;

		************************************/

	};
}

#endif // _TEXTURE_H