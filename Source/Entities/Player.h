#pragma once

#include "Entity.h"
#include "../Graphics/Animation.h"
#include "../GameStates/GameplayState.h"

#include <SDL_render.h>
#include <SDL_rect.h>

#include <optional>
#include <random>

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
			SDL_Rect hitSrc;
			SDL_Rect specialHitSrc;
			SDL_Rect healthSrc;
			SDL_Rect lostHealthSrc;
			gfx::Animation attacking;

			ControllableVisuals(SDL_Texture *spriteSheet, const SDL_Rect &hurtSrc, const SDL_Rect &hitSrc, const SDL_Rect &specialHitSrc, const SDL_Rect &healthSrc, const SDL_Rect &lostHealthSrc, const gfx::Animation &attacking) noexcept;
		};

		Player(const SDL_FPoint &pos, const gfx::Animation &animation, const std::optional<ControllableVisuals> &controllable, scene::Scene &scene, states::GameplayState *gameplayState, Game &game) noexcept;

		void update() noexcept override;
		void render(SDL_Renderer *renderer) const noexcept override;

	protected:
		void remove() noexcept override;

	private:
		scene::Scene &scene;
		const SDL_FPoint speed{7.5f, 7.0f};

		bool hurt{false};
		float hurtTimer{0.0f};
		const float hurtTime{1000.0f};
		bool knockback{false};

		bool canAttack{false};
		float timeSinceAttack{0.0f};
		bool showAttack{false};
		bool showHurt{false};
		bool usingSpecial{false};

		std::random_device device;

		gfx::Animation animation;
		std::optional<ControllableVisuals> controllableVisuals;

		states::GameplayState *gameplayState;
		Game &game;
	};
}