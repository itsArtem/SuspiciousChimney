#include "Player.h"
#include "../Scene/Scene.h"
#include "../Utility.h"
#include "../Game.h"
#include "../GameStates/GameOverState.h"

#include <SDL_keyboard.h>
#include <SDL_scancode.h>

#include <cstdint>

namespace sus::entities
{
	Player::ControllableVisuals::ControllableVisuals(SDL_Texture *spriteSheet, const SDL_Rect &hurtSrc, const SDL_Rect &hitSrc, const SDL_Rect &specialHitSrc, const SDL_Rect &healthSrc, const SDL_Rect &lostHealthSrc, const gfx::Animation &attacking) noexcept
		: spriteSheet{spriteSheet},
		hurtSrc{hurtSrc},
		hitSrc{hitSrc},
		specialHitSrc{specialHitSrc},
		healthSrc{healthSrc},
		lostHealthSrc{lostHealthSrc},
		attacking{attacking}
	{
	}

	Player::Player(const SDL_FPoint &pos, const gfx::Animation &animation, const std::optional<ControllableVisuals> &controllable, scene::Scene &scene, states::GameplayState *gameplayState, Game &game) noexcept
		: Entity{{pos, {74.0f, 96.0f}, {0.0f, 0.0f}, {3.0f, 3.0f}, {5.0f, 0.0f, 64.0f, 97.0f}}, {false, ConsumableType::none, 4}, scene.camera},
		scene{scene},
		animation{animation},
		controllableVisuals{controllable},
		gameplayState{gameplayState},
		game{game}
	{
	}

	void Player::update() noexcept
	{
		const SDL_FRect hitbox{tf.pos.x + tf.bounds.x, tf.pos.y + tf.bounds.y, tf.bounds.w, tf.bounds.h};
		bool attacking{false};

		constexpr int specialCost{3};
		usingSpecial = false;

		if (*properties.health > 0)
		{
			if (canAttack || !controllableVisuals)
				tf.velocity.y = speed.y;

			if (controllableVisuals)
			{
				if (!hurt)
				{
					const std::uint8_t *const keyboard{SDL_GetKeyboardState(nullptr)};

					if (keyboard[SDL_SCANCODE_A] || keyboard[SDL_SCANCODE_LEFT])
						tf.velocity.x = -speed.x;
					if (keyboard[SDL_SCANCODE_D] || keyboard[SDL_SCANCODE_RIGHT])
						tf.velocity.x = speed.x;

					timeSinceAttack += 1000.0f / game.ups;
					if ((keyboard[SDL_SCANCODE_SPACE] || keyboard[SDL_SCANCODE_F]) && canAttack)
					{
						attacking = true;
						canAttack = false;
						showAttack = true;
						timeSinceAttack = 0.0f;
						controllableVisuals->attacking.toBeginning();
					}
					else if (!keyboard[SDL_SCANCODE_SPACE] && !keyboard[SDL_SCANCODE_F])
						canAttack = true;

					if (keyboard[SDL_SCANCODE_S] && gameplayState && gameplayState->special >= specialCost)
						usingSpecial = true;

					if (showAttack && timeSinceAttack >= (controllableVisuals->attacking.getTimePerFrame() * 2) * controllableVisuals->attacking.getFrameCount())
						showAttack = false;
				}
				else if (knockback)
				{
					tf.velocity.y = -speed.y * 2;
					if (hurtTimer >= hurtTime * 0.2f)
						knockback = false;
				}
				else
					tf.velocity.y = 0.0f;

				scene.camera.pos.y = hitbox.y - hitbox.h + hitbox.h / 4;
			}

			const SDL_FRect attackRange{hitbox.x, hitbox.y + tf.velocity.y, hitbox.w, hitbox.h + 200.0f};

			for (auto &other : scene.entities)
			{
				if (other.get() == this)
					continue;

				const SDL_FRect otherHitbox{other->tf.pos.x + other->tf.bounds.x, other->tf.pos.y + other->tf.bounds.y, other->tf.bounds.w, other->tf.bounds.h};
				constexpr float ejectDist{0.1f};
				bool hit{false};
				bool collision{false};

				if (hasIntersection({hitbox.x + tf.velocity.x, hitbox.y, hitbox.w, hitbox.h}, otherHitbox))
				{
					const float left{otherHitbox.x + otherHitbox.w - hitbox.x};
					const float right{hitbox.x + hitbox.w - otherHitbox.x};

					if (other->properties.consumable == ConsumableType::none)
					{
						if (left < right)
							tf.pos.x += left + ejectDist;
						else
							tf.pos.x -= right + ejectDist;

						tf.velocity.x = 0.0f;
						//hit = true;
					}
					collision = true;
				}

				if (hasIntersection({hitbox.x, hitbox.y + tf.velocity.y, hitbox.w, hitbox.h}, otherHitbox))
				{
					const float up{otherHitbox.y + otherHitbox.h - hitbox.y};
					const float down{hitbox.y + hitbox.h - otherHitbox.y};

					if (other->properties.consumable == ConsumableType::none)
					{
						if (up < down)
							tf.pos.y += up + ejectDist;
						else
							tf.pos.y -= down + ejectDist;

						tf.velocity.y = 0.0f;
						hit = true;
					}
					collision = true;
				}

				if (collision)
				{
					if (other->properties.despawnOnCollision)
						other->active = false;

					if (gameplayState)
						if (other->properties.consumable == ConsumableType::special)
						{
							++gameplayState->special;
							other->active = false;
						}
						else if (other->properties.consumable == ConsumableType::health)
						{
							++properties.health.value();
							if (properties.health > properties.maxHealth)
							{
								properties.health = properties.maxHealth;
								++gameplayState->score;
							}

							other->active = false;
						}
				}

				if (controllableVisuals && hit && !hurt)
				{
					--properties.health.value();
					hurt = true;
					knockback = true;
				}

				if (hurt)
				{
					if (*properties.health > 0 && hurtTimer >= hurtTime)
					{
						hurt = false;
						hurtTimer = 0.0f;
					}
				}
				else if (attacking && other->properties.health && hasIntersection(attackRange, otherHitbox))
				{
					if (gameplayState && usingSpecial && gameplayState->special >= specialCost)
					{
						*other->properties.health -= 2;
						gameplayState->special -= specialCost;
					}
					else
						--other->properties.health.value();

					if (gameplayState && *other->properties.health == 0)
						++gameplayState->score;

					//attacking = false;
				}
			}
		}

		if (!hurt)
			if (timeSinceAttack && showAttack)
				controllableVisuals->attacking.update(game.ups);
			else
				animation.update(game.ups);
		else
		{
			hurtTimer += 1000.0f / game.ups;
			showHurt = device() % 2 == 0;
		}

		Entity::update();
	}

	void Player::render(SDL_Renderer *renderer) const noexcept
	{
		const SDL_FRect dst{getDestination()};

		if (controllableVisuals && *properties.health > 0)
		{
			for (int i = 0; i < *properties.health; ++i)
			{
				const SDL_FRect healthDst{(dst.x + 6) + 18 * i, dst.y - 18.0f, 18.0f, 18.0f};
				SDL_RenderCopyF(renderer, controllableVisuals->spriteSheet, &controllableVisuals->healthSrc, &healthDst);
			}

			for (int i = 0; i < properties.maxHealth - *properties.health; ++i)
			{
				const SDL_FRect healthDst{(dst.x + 6) + 18 * properties.maxHealth - 18 * i - 18, dst.y - 18.0f, 18.0f, 18.0f};
				SDL_RenderCopyF(renderer, controllableVisuals->spriteSheet, &controllableVisuals->lostHealthSrc, &healthDst);
			}
		}

		if (hurt && controllableVisuals)
		{
			if (showHurt)
				SDL_RenderCopyF(renderer, controllableVisuals->spriteSheet, &controllableVisuals->hurtSrc, &dst);
		}
		else if (showAttack)
		{
			controllableVisuals->attacking.render(renderer, dst);

			if (timeSinceAttack < 60.0f)
			{
				const SDL_FRect hitDst{dst.x, dst.y + tf.bounds.y + tf.bounds.h, dst.w, 32.0f};

				if (usingSpecial)
					SDL_RenderCopyF(renderer, controllableVisuals->spriteSheet, &controllableVisuals->specialHitSrc, &hitDst);
				else
					SDL_RenderCopyF(renderer, controllableVisuals->spriteSheet, &controllableVisuals->hitSrc, &hitDst);
			}
		}
		else
			animation.render(renderer, dst);
	}

	void Player::remove() noexcept
	{
		if (hurtTimer >= hurtTime / 2)
		{
			tf.velocity.y = -speed.y * 2;
			if (hurtTimer >= hurtTime * 2)
			{
				game.gameStateManager.popBack();
				game.gameStateManager.emplaceBack<states::GameOverState>(game, gameplayState->score, gameplayState->getHighscore());
			}
		}
		else
		{
			int windowHeight;
			SDL_GetWindowSize(game.getWindow(), nullptr, &windowHeight);

			const float target{tf.pos.y + tf.size.y + tf.size.y / 2 - windowHeight};
			if (scene.camera.pos.y > target)
			{
				scene.camera.pos.y -= 20.0f;
				if (scene.camera.pos.y < target)
					scene.camera.pos.y = target;
			}
		}
	}
}
