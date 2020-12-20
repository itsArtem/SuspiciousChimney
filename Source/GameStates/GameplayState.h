#pragma once

#include "GameState.h"
#include "../Game.h"
#include "../Scene/Scene.h"
#include "../Graphics/SnowScreen.h"

#include <SDL_render.h>
#include <SDL_rect.h>

#include <random>
#include <fstream>
#include <cstdint>

namespace sus::states
{
	class GameplayState final : public GameState
	{
	public:
		std::int32_t score{0};
		int special{0};
		const int maxSpecial{30};

		GameplayState(Game &game) noexcept;

		void update() noexcept override;
		void render() const noexcept override;

		// Done this way to control when memory for the entity vector is reallocated.
		void spawnSpecial(const SDL_FPoint &pos) noexcept { specialPositions.emplace_back(pos); }
		std::int32_t getHighscore() const noexcept { return highscore; }

	private:
		Game &game;
		scene::Scene scene{game};
		float chimneyPos{100.0f};
		const SDL_FPoint chimneySize{600.0f, 1200.0f};
		const float borderSize{9.0f};

		gfx::SnowScreen snow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};
		
		std::random_device device;
		std::default_random_engine engine{device()};
		std::uniform_int_distribution<int> spawnTypes{0, 6};
		std::uniform_real_distribution<float> spawnPos{chimneyPos + borderSize, chimneyPos + chimneySize.x - borderSize * 2};
		float lastSpawnHeight{0.0f};

		int levelsTravelled{0};
		const int initialSpawnChance{50};
		int difficulty{0};

		std::int32_t highscore{0};
		std::int32_t lastMilestone{0};
		int lastLevelsTravelled{0};

		const SDL_Rect specialIconSrc{0, 128, 8, 8};
		const SDL_Rect specialMetreSrc{8, 128, 120, 8};

		const SDL_FRect specialMetreDst{50.0f, 10.0f, 700.0f, 32.0f};
		std::vector<SDL_FPoint> specialPositions;

		std::fstream stream{"Resources/Highscore.sav", std::fstream::in | std::fstream::binary};
		bool pressedPause{false};

		void verifyPos(entities::Entity &entity) noexcept;
	};
}