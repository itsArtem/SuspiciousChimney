#pragma once

#include "GameState.h"
#include "../Scene/Scene.h"
#include "../Entities/Entitiy.h"
#include "../Graphics/SnowScreen.h"

#include <chrono>

namespace sus
{
	class Game;
}

namespace sus::states
{
	class CutsceneState final : public GameState
	{
	public:
		CutsceneState(Game &game) noexcept;

		void update() noexcept override;
		void render() const noexcept override;

	private:
		const Game &game;
		scene::Scene scene;

		const int chimneyLength{40};
		const entities::Entity *chimney{nullptr};

		float cameraVelocity{0.0f};
		const std::chrono::steady_clock::time_point spawnTime{std::chrono::steady_clock::now()};

		gfx::SnowScreen backgroundSnow;
		gfx::SnowScreen foregroundSnow;
	};
}