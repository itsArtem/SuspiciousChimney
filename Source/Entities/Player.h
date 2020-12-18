#pragma once

#include "Entitiy.h"
#include "../Graphics/Animation.h"

#include <SDL_render.h>
#include <SDL_rect.h>

namespace sus
{
	class Game;
}

namespace sus::scene
{
	class Scene;
}

namespace sus::entities
{
	class Player final : public Entity
	{
	public:
		Player(const SDL_FPoint &pos, const gfx::Animation &idle, const scene::Scene &scene, bool controllable, const Game &game) noexcept;

		void update() noexcept override;
		void render(SDL_Renderer *renderer) const noexcept override;

	private:
		const scene::Scene &scene;
		bool controllable;
		
		gfx::Animation idle;
		const Game &game;
	};
}