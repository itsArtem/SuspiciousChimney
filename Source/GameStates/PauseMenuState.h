#pragma once

#include "GameState.h"
#include "../Graphics/Button.h"
#include "../Game.h"
#include "../Graphics/SnowScreen.h"

#include <SDL_rect.h>

#include <array>
#include <memory>

namespace sus::states
{
	class PauseMenuState final : public GameState
	{
	public:
		PauseMenuState(Game &game) noexcept;

		void update() noexcept override;
		void render() const noexcept override;

	private:
		Game &game;
		std::array<gfx::Button, 3> buttons{
			gfx::Button{SDL_FPoint{400.0f, 200.0f}, std::make_unique<gfx::Text>("Resume", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true},
			gfx::Button{SDL_FPoint{400.0f, 240.0f}, std::make_unique<gfx::Text>("How to play", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true},
			gfx::Button{SDL_FPoint{400.0f, 280.0f}, std::make_unique<gfx::Text>("Main Menu", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true}
		};

		gfx::SnowScreen snow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};
		gfx::Text title{"Paused", game.fontCache[1], SDL_Colour{200, 30, 30, 255}, game.getRenderer()};
	};
}