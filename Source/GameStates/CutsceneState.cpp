#include "CutsceneState.h"
#include "../Game.h"
#include "../Graphics/TextureCache.h"
#include "../Entities/Player.h"
#include "../Entities/Roof.h"
#include "../Entities/Chimney.h"
#include "../Graphics/Animation.h"

#include <SDL_render.h>

#include <memory>

namespace sus::states
{
	CutsceneState::CutsceneState(Game &game) noexcept
		: game{game},
		scene{game},
		backgroundSnow{game.textureCache.load("Resources/Snow.png", game.getRenderer()), {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}},
		foregroundSnow{game.textureCache[0], {0.0f, 0.0f, 1600.0f, 1600.0f}, {-0.02f, 1.4f}}
	{
		SDL_Texture *const spriteSheet = game.textureCache.load("Resources/SpriteSheet.png", game.getRenderer());

		scene.entities.emplace_back(std::make_unique<entities::Player>(SDL_FPoint{300.0f, 248.0f}, gfx::Animation{spriteSheet, 2, {0, 0, 16, 23}, 350.0f}, scene, false, game));
		scene.entities.emplace_back(std::make_unique<entities::Roof>(SDL_FPoint{0.0f, 350.0f}, spriteSheet, SDL_Rect{0, 80, 128, 40}, scene.camera));

		chimney = scene.entities.emplace_back(std::make_unique<entities::Chimney>(SDL_FPoint{75.0f, 376.0f},
			spriteSheet,
			SDL_Rect{0, 56, 32, 24},
			SDL_Rect{0, 40, 32, 16},
			scene.camera, chimneyLength,
			SDL_FPoint{128.0f, 48.0f})).get();
	}

	void states::CutsceneState::update() noexcept
	{
		if (std::chrono::steady_clock::now() - spawnTime >= std::chrono::seconds{3})
		{
			constexpr float maxVelocity{26.0f};

			if (scene.camera.pos.y > chimney->pos.y - chimney->size.y * (chimneyLength - 1))
			{
				if (cameraVelocity < maxVelocity)
				{
					cameraVelocity += 0.1f;
					if (cameraVelocity > maxVelocity)
						cameraVelocity = maxVelocity;
				}
			}
			else if (cameraVelocity > 0.0f)
			{
				cameraVelocity *= 0.92f;
				if (cameraVelocity < 0.0f)
					cameraVelocity = 0.0f;
			}
			scene.camera.pos.y -= cameraVelocity;
		}

		backgroundSnow.update();
		scene.update();
		foregroundSnow.update();
	}

	void states::CutsceneState::render() const noexcept
	{
		SDL_Renderer *const renderer{game.getRenderer()};
		SDL_SetRenderDrawColor(renderer, 10, 10, 12, 0);
		SDL_RenderFillRect(renderer, nullptr);

		backgroundSnow.render(renderer);
		scene.render();
		foregroundSnow.render(renderer, SDL_FLIP_HORIZONTAL);
	}
}
