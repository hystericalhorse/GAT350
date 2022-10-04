#ifndef _GAME_H
#define _GAME_H

#include "Scene.h"
#include <iostream>

namespace en
{
	class Game
	{
	public:
		Game() = default;
		virtual ~Game() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void Update() = 0;
		virtual void Draw(Renderer& renderer) = 0;

		int return_score() { return _score; }
		void add_points(int points) { _score += points; }

	protected:
		std::unique_ptr<Scene> _scene;
		int _score = 0;

	};
}

#endif // _GAME_H