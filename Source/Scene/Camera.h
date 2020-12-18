#pragma once

#include <SDL_rect.h>

namespace sus
{
	class Game;
}

namespace sus::entities
{
	class Entity;
}

namespace sus::scene
{
	class Camera final
	{
	public:
		SDL_FPoint pos{0.0f, 0.0f};

		Camera(const Game &game) noexcept
			: game{game} { }
		
		Camera(const Game &game, const SDL_FPoint &pos) noexcept;

		void centre(const entities::Entity &entity) noexcept;

	private:
		const Game &game;
	};
}