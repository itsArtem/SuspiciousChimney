#pragma once

#include "GameState.h"
#include "../Game.h"
#include "../Scene/Scene.h"
#include "../Graphics/SnowScreen.h"

#include <SDL_render.h>
#include <SDL_rect.h>

#include <random>

namespace sus::states
{
	class GameplayState final : public GameState
	{
	public:
		GameplayState(Game &game) noexcept;

		void update() noexcept override;
		void render() const noexcept override;

	private:
		Game &game;
		scene::Scene scene{game};
		float chimneyPos{100.0f};
		const SDL_FPoint chimneySize{600.0f, 1200.0f};
		const float borderSize{9.0f};

		gfx::SnowScreen snow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};
		SDL_Texture *const chimney{game.textureCache.load("Resources/ChimneyInside.png", game.getRenderer())};

		std::random_device device;
		std::default_random_engine engine{device()};
		std::uniform_int_distribution<int> obsTypes{0, 5};
		std::uniform_real_distribution<float> obsPos{chimneyPos + borderSize, chimneyPos + chimneySize.x - borderSize * 2};
		float lastSpawnHeight{0.0f};

		int levelsTravelled{0};
	};
}