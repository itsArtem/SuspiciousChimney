#include "Camera.h"
#include "../Entities/Entitiy.h"
#include "../Game.h"

#include <SDL_video.h>

namespace sus::scene
{
	Camera::Camera(const Game &game, const SDL_FPoint &pos) noexcept
		: game{game},
		pos{pos}
	{
	}
	
	void Camera::centre(const entities::Entity &entity) noexcept
	{
		SDL_Point windowSize;
		SDL_GetWindowSize(game.getWindow(), &windowSize.x, &windowSize.y);

		pos.x = entity.pos.x + entity.size.x / 2 - windowSize.x / 2;
		pos.y = entity.pos.y + entity.size.y / 2 - windowSize.y / 2;
	}
}
