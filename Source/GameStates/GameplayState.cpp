#include "GameplayState.h"
#include "../Entities/Player.h"
#include "../Entities/Entity.h"
#include "../Graphics/Animation.h"
#include "../Entities/Hostiles.h"

#include <SDL_video.h>

namespace sus::states
{
	GameplayState::GameplayState(Game &game) noexcept
		: game{game}
	{
		scene.entities.emplace_back(std::make_unique<entities::Player>(SDL_FPoint{chimneyPos + chimneySize.x / 2 - 55.0f, 0.0f},
			gfx::Animation{game.textureCache[0], 2, {32, 0, 16, 24}, 250.0f, true},
			entities::Player::ControllableVisuals{game.textureCache[0], {64, 0, 16, 24}, gfx::Animation{game.textureCache[0], 3, {80, 0, 16, 24}, 40.0f, false}},
			scene,
			game));
	}

	void GameplayState::update() noexcept
	{
		snow.update();

		entities::Entity &player = *scene.entities[0];
		scene.update();

		int windowHeight;
		SDL_GetWindowSize(game.getWindow(), nullptr, &windowHeight);

		if (player.tf.pos.x + player.tf.bounds.x < chimneyPos + borderSize)
			player.tf.pos.x = chimneyPos + borderSize - player.tf.bounds.x;
		else if (player.tf.pos.x + player.tf.bounds.x + player.tf.bounds.w > chimneyPos + chimneySize.x - borderSize * 2)
			player.tf.pos.x = (chimneyPos + chimneySize.x - borderSize * 2) - player.tf.bounds.x - player.tf.bounds.w;

		if (player.tf.pos.y > chimneySize.y * (levelsTravelled + 1) + windowHeight / 2)
			++levelsTravelled;

		if (device() % 40 == 0)
		{
			const float spawnHeight{player.tf.pos.y + chimneySize.y};

			switch (obsTypes(engine))
			{
			case 0:
			{
				float pos{obsPos(engine)};
				if (pos > chimneyPos + chimneySize.x - borderSize * 2 - 72.0f)
					pos = chimneyPos + chimneySize.x - borderSize * 2 - 72.0f;
				if (spawnHeight - lastSpawnHeight < 72.0f)
					return;

				scene.entities.emplace_back(std::make_unique<entities::Spikes>(SDL_FPoint{pos, spawnHeight},
					game.textureCache[0],
					SDL_Rect{0, 24, 16, 16},
					scene.camera));
				break;
			}
			case 1:
			{
				float pos{obsPos(engine)};
				if (pos > chimneyPos + chimneySize.x - borderSize * 2 - 72.0f)
					pos = chimneyPos + chimneySize.x - borderSize * 2 - 72.0f;
				if (spawnHeight - lastSpawnHeight < 72.0f)
					return;

				scene.entities.emplace_back(std::make_unique<entities::Spikes>(SDL_FPoint{pos, spawnHeight},
					game.textureCache[0],
					SDL_Rect{16, 24, 16, 16},
					scene.camera));
				break;
			}
			case 2:
			{
				float pos{obsPos(engine)};
				if (pos > chimneyPos + chimneySize.x - borderSize * 2 - 80.0f)
					pos = chimneyPos + chimneySize.x - borderSize * 2 - 80.0f;
				if (spawnHeight - lastSpawnHeight < 128.0f)
					return;

				scene.entities.emplace_back(std::make_unique<entities::CandyCane>(SDL_FPoint{pos, spawnHeight},
					game.textureCache[0],
					SDL_Rect{32, 24, 16, 24},
					scene.camera));
				break;
			}
			case 3:
			{
				float pos{obsPos(engine)};
				if (pos > chimneyPos + chimneySize.x - borderSize * 2 - 128.0f)
					pos = chimneyPos + chimneySize.x - borderSize * 2 - 128.0f;
				if (spawnHeight - lastSpawnHeight < 256.0f)
					return;

				scene.entities.emplace_back(std::make_unique<entities::Tentacle>(SDL_FPoint{pos, spawnHeight},
					game.textureCache[0],
					SDL_Rect{48, 24, 24, 48},
					scene.camera));
				break;
			}
			case 4:
			{
				float pos{obsPos(engine)};
				if (pos > chimneyPos + chimneySize.x - borderSize * 2 - 96.0f)
					pos = chimneyPos + chimneySize.x - borderSize * 2 - 96.0f;
				if (spawnHeight - lastSpawnHeight < 96.0f)
					return;

				scene.entities.emplace_back(std::make_unique<entities::Demon>(SDL_FPoint{pos, spawnHeight},
					gfx::Animation{game.textureCache[0], 2, {72, 24, 16, 16}, 200.0f, true},
					scene.camera,
					game));
				break;
			}
			case 5:
			{
				float pos{obsPos(engine)};
				if (pos > chimneyPos + chimneySize.x - borderSize * 2 - 72.0f)
					pos = chimneyPos + chimneySize.x - borderSize * 2 - 72.0f;
				if (spawnHeight - lastSpawnHeight < 72.0f)
					return;

				scene.entities.emplace_back(std::make_unique<entities::Wall>(SDL_FPoint{pos, spawnHeight},
					game.textureCache[0],
					SDL_Rect{32, 64, 16, 16},
					scene.camera));
				break;
			}
			}

			lastSpawnHeight = spawnHeight;
		}
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
	}
}