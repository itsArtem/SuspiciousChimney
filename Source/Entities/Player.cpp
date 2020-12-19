#include "Player.h"
#include "../Scene/Scene.h"
#include "../Utility.h"
#include "../Game.h"
#include "../GameStates/GameOverState.h"

#include <SDL_keyboard.h>

#include <utility>
#include <cstdint>

namespace sus::entities
{
	Player::ControllableVisuals::ControllableVisuals(SDL_Texture *spriteSheet, SDL_Rect hurtSrc, const gfx::Animation &attacking) noexcept
		: spriteSheet{spriteSheet},
		hurtSrc{hurtSrc},
		attacking{attacking}
	{
	}

	Player::Player(const SDL_FPoint &pos, const gfx::Animation &animation, std::optional<ControllableVisuals> &&controllable, scene::Scene &scene, Game &game) noexcept
		: Entity{{pos, {74.0f, 96.0f}, {0.0f, 0.0f}, {3.0f, 3.0f}, {5.0f, 0.0f, 64.0f, 97.0f}}, {}, scene.camera},
		scene{scene},
		animation{animation},
		controllableVisuals{std::move(controllable)},
		game{game}
	{
	}

	void Player::update() noexcept
	{
		Entity::update();

		if (!lost)
		{
			bool attacking{false};

			const SDL_FRect hitbox{tf.pos.x + tf.bounds.x, tf.pos.y + tf.bounds.y, tf.bounds.w, tf.bounds.h};
			constexpr SDL_FPoint speed{6.5f, 10.0f};

			if (controllableVisuals)
			{
				const std::uint8_t *const keyboard{SDL_GetKeyboardState(nullptr)};
				timeSinceAttack += 1000.0f / game.ups;

				if (keyboard[SDL_SCANCODE_A] || keyboard[SDL_SCANCODE_LEFT])
					tf.velocity.x = -speed.x;
				if (keyboard[SDL_SCANCODE_D] || keyboard[SDL_SCANCODE_RIGHT])
					tf.velocity.x = speed.x;

				if (keyboard[SDL_SCANCODE_SPACE] && canAttack)
				{
					attacking = true;
					canAttack = false;

					controllableVisuals->attacking.toBeginning();
					timeSinceAttack = 0.0f;
					showAttack = true;
				}
				else if (!keyboard[SDL_SCANCODE_SPACE])
					canAttack = true;
					
				scene.camera.pos.y = hitbox.y - hitbox.h / 2;
				if (scene.camera.pos.y < 0.0f)
					scene.camera.pos.y = 0.0f;
			}

			const SDL_FRect attackRange{hitbox.x, hitbox.y, hitbox.w, hitbox.h + 80.0f};

			if (!attacking)
			{
				if (tf.velocity.y < speed.y)
				{
					tf.velocity.y += speed.y * 0.35f;
					if (tf.velocity.y > speed.y)
						tf.velocity.y = speed.y;
				}
			}
			else
				tf.velocity.y = 0;

			for (auto &other : scene.entities)
			{
				if (other.get() == this)
					continue;

				const SDL_FRect otherHitbox{other->tf.pos.x + other->tf.bounds.x, other->tf.pos.y + other->tf.bounds.y, other->tf.bounds.w, other->tf.bounds.h};
				constexpr float ejectDist{0.1f};

				if (hasIntersection({hitbox.x + tf.velocity.x, hitbox.y, hitbox.w, hitbox.h}, otherHitbox))
				{
					const float left{otherHitbox.x + otherHitbox.w - hitbox.x};
					const float right{hitbox.x + hitbox.w - otherHitbox.x};

					if (left < right)
						tf.pos.x += left + ejectDist;
					else
						tf.pos.x -= right + ejectDist;

					tf.velocity.x = 0.0f;
					if (controllableVisuals)
						lost = true;
				}

				if (hasIntersection({hitbox.x, hitbox.y + tf.velocity.y, hitbox.w, hitbox.h}, otherHitbox))
				{
					const float up{otherHitbox.y + otherHitbox.h - hitbox.y};
					const float down{hitbox.y + hitbox.h - otherHitbox.y};

					if (up < down)
						tf.pos.y += up + ejectDist;
					else
						tf.pos.y -= down + ejectDist;

					tf.velocity.y = 0.0f;
					if (controllableVisuals)
						lost = true;
				}

				if (attacking && other->health && hasIntersection(attackRange, otherHitbox))
				{
					--other->health.value();
					attacking = false;
				}
			}

			if (timeSinceAttack >= controllableVisuals->attacking.getTimePerFrame() * controllableVisuals->attacking.getFrameCount())
				showAttack = false;
			
			if (showAttack)
				controllableVisuals->attacking.update(game.ups);
			else
				animation.update(game.ups);
		}
		else
		{
			lostTime += 1000.0f / game.ups;
			if (lostTime >= 800.0f)
			{
				tf.velocity.y = -20.0f;
				if (lostTime >= 2500.0f)
				{
					game.gameStateManager.popBack();
					game.gameStateManager.emplaceBack<states::GameOverState>();
				}
			}
		}
	}

	void Player::render(SDL_Renderer *renderer) const noexcept
	{
		if (lost && controllableVisuals)
		{
			if (static_cast<int>(lostTime) % 4 == 0)
				SDL_RenderCopyF(renderer, controllableVisuals->spriteSheet, &controllableVisuals->hurtSrc, &getDestination());
		}
		else if (showAttack)
			controllableVisuals->attacking.render(renderer, getDestination());
		else
			animation.render(renderer, getDestination());
	}
}
