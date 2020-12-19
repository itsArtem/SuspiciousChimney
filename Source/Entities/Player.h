#pragma once

#include "Entity.h"
#include "../Graphics/Animation.h"

#include <SDL_render.h>
#include <SDL_rect.h>

#include <optional>

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
		struct ControllableVisuals final
		{
			SDL_Texture *spriteSheet;
			SDL_Rect hurtSrc;
			gfx::Animation attacking;

			ControllableVisuals(SDL_Texture *spriteSheet, SDL_Rect hurtSrc, const gfx::Animation &attacking) noexcept;
		};

		Player(const SDL_FPoint &pos, const gfx::Animation &animation, std::optional<ControllableVisuals> &&controllable, scene::Scene &scene, Game &game) noexcept;

		void update() noexcept override;
		void render(SDL_Renderer *renderer) const noexcept override;

	private:
		scene::Scene &scene;
		bool lost{false};
		float lostTime{0.0f};

		bool canAttack{false};
		float timeSinceAttack{0.0f};
		bool showAttack{false};

		gfx::Animation animation;
		std::optional<ControllableVisuals> controllableVisuals;

		Game &game;
	};
}