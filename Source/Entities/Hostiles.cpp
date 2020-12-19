#include "Hostiles.h"

namespace sus::entities
{
	Spikes::Spikes(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept
		: Entity{{pos, {72.0f, 72.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 72.0f, 72.0f}}, 1, camera},
		texture{texture},
		src{src}
	{
	}
	
	CandyCane::CandyCane(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept
		: Entity{{pos, {80.0f, 128.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 80.0f, 128.0f}}, 1, camera},
		texture{texture},
		src{src}
	{
	}
	
	Tentacle::Tentacle(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept
		: Entity{{pos, {128.0f, 256.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 128.0f, 256.0f}}, 2, camera},
		texture{texture},
		src{src}
	{
	}

	Demon::Demon(const SDL_FPoint &pos, const gfx::Animation &animation, const scene::Camera &camera, const Game &game) noexcept
		: Entity{{pos, {96.0f, 96.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 96.0f, 96.0f}}, 2, camera},
		animation{animation},
		game{game}
	{
	}

	void Demon::update() noexcept
	{
		Entity::update();
		animation.update(game.ups);
	}

	Wall::Wall(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept
		: Entity{{pos, {72.0f, 72.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 72.0f, 72.0f}}, {}, camera},
		texture{texture},
		src{src}
	{
	}
}
