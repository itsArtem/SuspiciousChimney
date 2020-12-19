#include "Camera.h"
#include "../Entities/Entity.h"
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
		centreHorizontally(entity);
		centreVertically(entity);
	}
	
	void Camera::centreHorizontally(const entities::Entity &entity) noexcept
	{
		int windowWidth;
		SDL_GetWindowSize(game.getWindow(), &windowWidth, nullptr);

		pos.x = entity.tf.pos.x + entity.tf.size.x / 2 - windowWidth / 2;
	}
	
	void Camera::centreVertically(const entities::Entity &entity) noexcept
	{
		int windowHeight;
		SDL_GetWindowSize(game.getWindow(), nullptr, &windowHeight);

		pos.y = entity.tf.pos.y + entity.tf.size.y / 2 - windowHeight / 2;
	}
}
