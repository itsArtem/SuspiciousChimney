#include "CutsceneState.h"
#include "../Graphics/TextureCache.h"
#include "../Entities/Player.h"
#include "../Entities/Roof.h"
#include "../Graphics/Animation.h"
#include "../GameStates/GameplayState.h"
#include "../GameStates/PauseMenuState.h"
#include "../AudioCache.h"

#include <SDL_render.h>
#include <SDL_keyboard.h>
#include <SDL_scancode.h>
#include <SDL_mixer.h>

#include <optional>
#include <cstdint>

namespace sus::states
{
	CutsceneState::CutsceneState(Game &game) noexcept
		: game{game}
	{
		scene.entities.emplace_back(std::make_unique<entities::Player>(SDL_FPoint{300.0f, 248.0f},
			gfx::Animation{game.textureCache[0], 2, {0, 0, 16, 23}, 350.0f, true},
			std::optional<entities::Player::ControllableVisuals>{},
			scene,
			nullptr,
			game));

		scene.entities.emplace_back(std::make_unique<entities::Roof>(SDL_FPoint{0.0f, 350.0f}, game.textureCache[0], SDL_Rect{0, 80, 128, 40}, scene.camera));
	}

	void states::CutsceneState::update() noexcept
	{
		const std::uint8_t *keyboard{SDL_GetKeyboardState(nullptr)};
		if (keyboard[SDL_SCANCODE_ESCAPE])
			pressedPause = true;
		else if (!keyboard[SDL_SCANCODE_ESCAPE] && pressedPause)
		{
			game.gameStateManager.emplaceBack<states::PauseMenuState>(game);
			pressedPause = false;
			Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
		}

		if (keyboard[SDL_SCANCODE_SPACE])
			pressedSkip = true;
		else if (pressedSkip)
		{
			startGame();
			Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
		}

		timePassed += 1.0f / game.ups;
		if (timePassed >= 3.0f)
		{
			constexpr float maxVelocity{26.0f};

			if (scene.camera.pos.y > chimney->tf.pos.y - chimney->tf.size.y * (chimneyLength - 1))
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

			if (timePassed >= 10.0f)
				startGame();

			if (static_cast<int>(skipMsg.mod.a) - 5 > 0)
				skipMsg.mod.a -= 5;
			else
				skipMsg.mod.a = 0;
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

		if (skipMsg.mod.a > 0)
		{
			SDL_Point windowSize;
			SDL_GetWindowSize(game.getWindow(), &windowSize.x, &windowSize.y);
			skipMsg.render({windowSize.x - skipMsg.getSize().x + 0.0f, windowSize.y - skipMsg.getSize().y + 0.0f});
		}
	}

	void CutsceneState::startGame() const noexcept
	{
		game.gameStateManager.popBack();
		game.gameStateManager.emplaceBack<GameplayState>(game);
	}
}
