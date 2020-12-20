#include "GameplayState.h"
#include "../Entities/Player.h"
#include "../Entities/Entity.h"
#include "../Graphics/Animation.h"
#include "../Entities/Hostiles.h"
#include "../Entities/Consumable.h"
#include "../Utility.h"

#include <SDL_video.h>

namespace sus::states
{
	GameplayState::GameplayState(Game &game) noexcept
		: game{game}
	{
		scene.entities.emplace_back(std::make_unique<entities::Player>(SDL_FPoint{chimneyPos + chimneySize.x / 2 - 55.0f, 0.0f},
			gfx::Animation{game.textureCache[0], 2, {32, 0, 16, 24}, 250.0f, true},
			entities::Player::ControllableVisuals{
				game.textureCache[0], 
				{64, 0, 16, 24}, {104, 24, 16, 8}, {104, 32, 16, 8}, {120, 24, 8, 8}, {120, 32, 8, 8}, gfx::Animation{game.textureCache[0], 3, {80, 0, 16, 24}, 40.0f, false}
			},
			scene,
			this,
			game));
	}

	void GameplayState::update() noexcept
	{
		snow.update();
		entities::Entity &player = *scene.entities[0];
		
		scene.update();
		
		if (scene.camera.pos.y < chimneySize.y * levelsTravelled)
			scene.camera.pos.y = chimneySize.y * levelsTravelled;

		int windowHeight;
		SDL_GetWindowSize(game.getWindow(), nullptr, &windowHeight);

		if (player.tf.pos.x + player.tf.bounds.x < chimneyPos + borderSize)
			player.tf.pos.x = chimneyPos + borderSize - player.tf.bounds.x;
		else if (player.tf.pos.x + player.tf.bounds.x + player.tf.bounds.w > chimneyPos + chimneySize.x - borderSize)
			player.tf.pos.x = (chimneyPos + chimneySize.x - borderSize) - player.tf.bounds.x - player.tf.bounds.w;

		if (player.tf.pos.y > chimneySize.y * (levelsTravelled + 1) + windowHeight / 2)
			++levelsTravelled;

		if (difficulty >= initialSpawnChance || device() % (initialSpawnChance - difficulty) == 0)
		{
			const float spawnHeight{player.tf.pos.y + chimneySize.y + chimneySize.y / 2};

			switch (spawnTypes(engine))
			{
			case 0:
				scene.entities.emplace_back(std::make_unique<entities::Spikes>(SDL_FPoint{spawnPos(engine), spawnHeight},
					game.textureCache[0],
					SDL_Rect{0, 24, 16, 16},
					scene.camera,
					*this));
				break;
			case 1:
				scene.entities.emplace_back(std::make_unique<entities::Spikes>(SDL_FPoint{spawnPos(engine), spawnHeight},
					game.textureCache[0],
					SDL_Rect{16, 24, 16, 16},
					scene.camera,
					*this));
				break;
			case 2:
				scene.entities.emplace_back(std::make_unique<entities::CandyCane>(SDL_FPoint{spawnPos(engine), spawnHeight},
					game.textureCache[0],
					SDL_Rect{32, 24, 16, 24},
					scene.camera,
					*this));
				break;
			case 3:
				scene.entities.emplace_back(std::make_unique<entities::TentacleMonster>(SDL_FPoint{spawnPos(engine), spawnHeight},
					gfx::Animation{game.textureCache[0], 3, {48, 40, 24, 32}, 200.0f, true},
					scene.camera,
					*this,
					game));
				break;
			case 4:
				scene.entities.emplace_back(std::make_unique<entities::Demon>(SDL_FPoint{spawnPos(engine), spawnHeight},
					gfx::Animation{game.textureCache[0], 2, {48, 24, 16, 16}, 100.0f, true},
					scene.camera,
					*this,
					game));
				break;
			case 5:
				scene.entities.emplace_back(std::make_unique<entities::Wall>(SDL_FPoint{spawnPos(engine), spawnHeight},
					game.textureCache[0],
					SDL_Rect{32, 64, 16, 16},
					scene.camera,
					*this));
				break;
			case 6:
				scene.entities.emplace_back(std::make_unique<entities::Consumable>(SDL_FPoint{spawnPos(engine), spawnHeight}, 
					game.textureCache[0], 
					SDL_Rect{120, 48, 8, 8}, 
					entities::ConsumableType::health, 
					scene, 
					0));
				break;
			}

			verifyPos(*scene.entities.back());
			lastSpawnHeight = spawnHeight;
		}

		if (levelsTravelled - lastLevelsTravelled > 5)
		{
			++score;
			lastLevelsTravelled = levelsTravelled;
		}

		if (difficulty < 100 && score - lastMilestone > 5)
		{
			difficulty += 5;
			lastMilestone = score;
		}

		for (auto &entity : scene.entities)
			if (entity.get() != &player && entity->tf.pos.y + entity->tf.size.x < scene.camera.pos.y - chimneySize.y)
				entity->active = false;

		for (auto it{specialPositions.begin()}; it != specialPositions.end();)
		{
			scene.entities.emplace_back(std::make_unique<entities::Consumable>(*it, game.textureCache[0], SDL_Rect{120, 40, 8, 8}, entities::ConsumableType::special, scene, 0));
			it = specialPositions.erase(it);
		}

		if (special > maxSpecial)
			special = maxSpecial;
	}

	void GameplayState::render() const noexcept
	{
		SDL_Renderer *const renderer{game.getRenderer()};
		SDL_SetRenderDrawColor(renderer, 10, 10, 12, 0);
		SDL_RenderFillRect(renderer, nullptr);

		snow.render(renderer);

		const SDL_FRect firstDst{chimneyPos - scene.camera.pos.x, chimneySize.y * levelsTravelled - scene.camera.pos.y, chimneySize.x, chimneySize.y};
		const SDL_FRect secondDst{firstDst.x, chimneySize.y * (levelsTravelled + 1) - scene.camera.pos.y, firstDst.w, firstDst.h};
		SDL_RenderCopyF(renderer, chimney, nullptr, &firstDst);
		SDL_RenderCopyF(renderer, chimney, nullptr, &secondDst);

		scene.render();

		const SDL_FRect specialIconDst{specialMetreDst.x + specialMetreDst.w * special / maxSpecial - 19, specialMetreDst.y, 38.0f, 36.0f};
		SDL_RenderCopyF(renderer, game.textureCache[0], &specialMetreSrc, &specialMetreDst);
		SDL_RenderCopyF(renderer, game.textureCache[0], &specialIconSrc, &specialIconDst);
	}

	/* Not the most efficient solution, buuutt it's only a 48-hour game lol. */
	void GameplayState::verifyPos(entities::Entity &entity) noexcept
	{
		if (entity.tf.pos.x + entity.tf.bounds.x < chimneyPos + borderSize)
			entity.tf.pos.x = chimneyPos + entity.tf.bounds.x;
		else if (entity.tf.pos.x + entity.tf.bounds.x + entity.tf.bounds.w > chimneyPos + chimneySize.x - borderSize)
			entity.tf.pos.x = chimneyPos + chimneySize.x - borderSize - entity.tf.bounds.x - entity.tf.bounds.w;

		SDL_FRect area{entity.tf.pos.x, entity.tf.pos.y, entity.tf.size.x, entity.tf.size.y};
		bool check{true};

		while (check)
		{
			check = false;
			for (const auto &other : scene.entities)
			{
				if (other.get() == &entity)
					continue;

				const SDL_FRect otherArea{other->tf.pos.x, other->tf.pos.y, other->tf.size.x, other->tf.size.y};
				while (hasIntersection(area, otherArea))
				{
					entity.tf.pos.y += area.h;
					area.y += area.h;
					check = true;
				}
			}
		}
	}
}