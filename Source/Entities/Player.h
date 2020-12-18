#pragma once

#include "Entitiy.h"

#include <SDL_render.h>
#include <SDL_rect.h>

namespace sus::scene
{
	class Scene;
}

namespace sus::entities
{
	class Player final : public Entity
	{
	public:
		struct IdleTexture final
		{
			SDL_Texture *texture;
			SDL_Rect src;

			IdleTexture(SDL_Texture *texture, SDL_Rect src) noexcept;
		};

		Player(const SDL_FPoint &pos, const IdleTexture &idle, const scene::Scene &scene, bool controllable) noexcept;

		void update() noexcept override;
		void render(SDL_Renderer *renderer) const noexcept override;

	private:
		const scene::Scene &scene;
		const IdleTexture idle;
		bool controllable;
	};
}