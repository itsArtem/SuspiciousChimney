#include "Consumable.h"
#include "../Scene/Scene.h"

#include <cmath>

namespace sus::entities
{
	Consumable::Consumable(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, ConsumableType type, const scene::Scene &scene, std::size_t player) noexcept
		: Entity{{pos, {32.0f, 32.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 32.0f, 32.0f}}, {false, type, {}}, scene.camera},
		texture{texture},
		src{src},
		scene{scene},
		player{player}
	{
	}

	void Consumable::update() noexcept
	{
		if (properties.consumable == ConsumableType::special)
		{
			constexpr float speed{6.0f};
			const Entity &playerEntity{*scene.entities[player]};

			// Casting because of warning arithmetic overflow.
			const double angle{std::atan2(playerEntity.tf.pos.y - static_cast<double>(tf.pos.y), playerEntity.tf.pos.x - static_cast<double>(tf.pos.x)) * -180 / M_PI};

			tf.velocity.x = static_cast<float>(std::cos(angle * M_PI / -180) * speed);
			tf.velocity.y = static_cast<float>(std::sin(angle * M_PI / -180) * speed);
		}

		Entity::update();
	}
}
