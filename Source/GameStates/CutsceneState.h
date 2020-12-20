#pragma once

#include "GameState.h"
#include "../Game.h"
#include "../Scene/Scene.h"
#include "../Entities/Entity.h"
#include "../Entities/Chimney.h"
#include "../Graphics/SnowScreen.h"
#include "../Graphics/Text.h"

#include <SDL_pixels.h>
#include <SDL_rect.h>

#include <memory>

namespace sus::states
{
	class CutsceneState final : public GameState
	{
	public:
		CutsceneState(Game &game) noexcept;

		void update() noexcept override;
		void render() const noexcept override;

	private:
		Game &game;
		scene::Scene scene{game};

		const int chimneyLength{40};
		const entities::Entity *chimney{
			scene.entities.emplace_back(std::make_unique<entities::Chimney>(SDL_FPoint{75.0f, 376.0f},
			game.textureCache[0],
			SDL_Rect{0, 56, 32, 24},
			SDL_Rect{0, 40, 32, 16},
			scene.camera, chimneyLength,
			SDL_FPoint{128.0f, 48.0f})).get()
		};

		float cameraVelocity{0.0f};
		float timePassed{0.0f};
		bool pressedSkip{false};

		gfx::SnowScreen backgroundSnow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};
		gfx::SnowScreen foregroundSnow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {-0.02f, 1.4f}};

		gfx::Text skipMsg{"Press Space to skip.", game.fontCache[0], SDL_Colour{30, 30, 80, 255}, game.getRenderer()};
		bool pressedPause{false};

		void startGame() const noexcept;
	};
}