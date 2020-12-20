#include "Hostiles.h"
#include "../Scene/Scene.h"
#include "../Game.h"
#include "../GameStates/GameplayState.h"

#include <memory>
#include <cmath>

namespace sus::entities
{
	void Hostile::remove() noexcept
	{
		gameplay.spawnSpecial({tf.pos.x + tf.size.x / 2, tf.pos.y + tf.size.y / 2});
		active = false;
	}

	Hostile::Hostile(const Transform &tf, Properties properties, const scene::Camera &camera, states::GameplayState &gameplay) noexcept
		: Entity{tf, properties, camera},
		gameplay{gameplay}
	{
	}

	Spikes::Spikes(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera, states::GameplayState &gameplay) noexcept
		: Hostile{{pos, {72.0f, 72.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 72.0f, 72.0f}}, {false, ConsumableType::none, 5}, camera, gameplay},
		texture{texture},
		src{src}
	{
	}
	
	CandyCane::CandyCane(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera, states::GameplayState &gameplay) noexcept
		: Hostile{{pos, {80.0f, 128.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 80.0f, 128.0f}}, {false, ConsumableType::none, 5}, camera, gameplay},
		texture{texture},
		src{src}
	{
	}
	
	TentacleMonster::TentacleMonster(const SDL_FPoint &pos, const gfx::Animation &animation, const scene::Camera &camera, states::GameplayState &gameplay, const Game &game) noexcept
		: Hostile{{pos, {96.0f, 132.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 96.0f, 132.0f}}, {false, ConsumableType::none, 6}, camera, gameplay},
		animation{animation},
		game{game}
	{
	}

	void TentacleMonster::update() noexcept
	{
		Entity::update();
		animation.update(game.ups);
	}

	Demon::Demon(const SDL_FPoint &pos, const gfx::Animation &animation, const scene::Camera &camera, states::GameplayState &gameplay, const Game &game) noexcept
		: Hostile{{pos, {96.0f, 96.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 96.0f, 96.0f}}, {true, ConsumableType::none, 6}, camera, gameplay},
		animation{animation},
		game{game}
	{
	}

	void Demon::update() noexcept
	{
		animation.update(game.ups);

		move += 0.05f;
		if (move > 360.0f)
			move = 0.0f;
		
		tf.velocity.x = std::cos(move) * 10.0f;
		tf.velocity.y = -6.0f;

		if (tf.pos.x < 110.0f)
			tf.pos.x = 110.0f;
		else if (tf.pos.x + tf.size.x > 690.0f)
			tf.pos.x = 690.0f - tf.size.x;
		
		Entity::update();
	}

	Wall::Wall(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera, states::GameplayState &gameplay) noexcept
		: Hostile{{pos, {72.0f, 72.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 0.0f, 72.0f, 72.0f}}, {false, ConsumableType::none, 8}, camera, gameplay},
		texture{texture},
		src{src}
	{
	}
}
