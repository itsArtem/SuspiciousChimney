#pragma once

#include "Entity.h"

#include <SDL_render.h>
#include <SDL_rect.h>

#include <random>
#include <cstddef>

namespace sus::scene
{
	class Scene;
}

namespace sus::entities
{
	class Consumable final : public Entity
	{
	public:
		Consumable(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, ConsumableType type, const scene::Scene &scene, std::size_t player) noexcept;

		void update() noexcept override;
		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyExF(renderer, texture, &src, &getDestination(), angle, nullptr, SDL_FLIP_NONE);
		}

	private:
		SDL_Texture *const texture;
		const SDL_Rect src;
		const scene::Scene &scene;
		const std::size_t player;

		std::default_random_engine engine{std::random_device{}()};
		std::uniform_real_distribution<float> dist{0.0f, 360.0f};

		const double angle{dist(engine)};
	};
}