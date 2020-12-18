#include "Player.h"
#include "../Scene/Scene.h"
#include "../Utility.h"

#include "SDL_keyboard.h"

#include <cstdint>

namespace sus::entities
{
	Player::IdleTexture::IdleTexture(SDL_Texture *texture, SDL_Rect src) noexcept
		: texture{texture},
		src{src}
	{
	}

	Player::Player(const SDL_FPoint &pos, const IdleTexture &idle, const scene::Scene &scene, bool controllable) noexcept
		: Entity{pos, {74.0f, 96.0f}, {0.0f, 0.0f}, {3.0f, 3.0f}, {5.0f, 5.0f, 55.0f, 92.0f}, scene.camera},
		idle{idle},
		scene{scene},
		controllable{controllable}
	{
	}

	void Player::update() noexcept
	{
		Entity::update();

		constexpr SDL_FPoint speed{3.0f, 10.0f};
		velocity.y = speed.y;

		if (controllable)
		{
			const std::uint8_t *const keyboard{SDL_GetKeyboardState(nullptr)};

			if (keyboard[SDL_SCANCODE_A])
				velocity.x = -speed.x;
			if (keyboard[SDL_SCANCODE_D])
				velocity.x = speed.x;
		}

		const SDL_FRect hitbox{pos.x + bounds.x, pos.y + bounds.y, bounds.w, bounds.h};
		for (const auto &other : scene.entities)
		{
			if (other.get() == this)
				continue;

			const SDL_FRect otherHitbox{other->pos.x + other->bounds.x, other->pos.y + other->bounds.y, other->bounds.w, other->bounds.h};
			constexpr float ejectDist{0.1f};

			if (hasIntersection({hitbox.x + velocity.x, hitbox.y, hitbox.w, hitbox.h}, otherHitbox))
			{
				const float left{otherHitbox.x + otherHitbox.w - hitbox.x};
				const float right{hitbox.x + hitbox.w - otherHitbox.x};

				if (left < right)
					pos.x += left + ejectDist;
				else
					pos.x -= right + ejectDist;

				velocity.x = 0.0f;
			}

			if (hasIntersection({hitbox.x, hitbox.y + velocity.y, hitbox.w, hitbox.h}, otherHitbox))
			{
				const float up{otherHitbox.y + otherHitbox.h - hitbox.y};
				const float down{hitbox.y + hitbox.h - otherHitbox.y};
				
				if (up < down)
					pos.y += up + ejectDist;
				else
					pos.y -= down + ejectDist;

				velocity.y = 0.0f;
			}
		}
	}

	void Player::render(SDL_Renderer *renderer) const noexcept
	{
		if (!controllable)
			SDL_RenderCopyF(renderer, idle.texture, &idle.src, &getDestination());
	}
}
