#pragma once

#include "GameState.h"
#include "../Graphics/Button.h"
#include "../Game.h"
#include "../Graphics/SnowScreen.h"

#include <SDL_pixels.h>
#include <SDL_rect.h>

#include <array>
#include <memory>

namespace sus::states
{
	class MainMenuState final : public GameState
	{
	public:
		MainMenuState(Game &game) noexcept;

		void update() noexcept override;
		void render() const noexcept override;

	private:
		Game &game;
		std::array<gfx::Button, 4> buttons{
			gfx::Button{SDL_FPoint{400.0f, 230.0f}, std::make_unique<gfx::Text>("Play", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true},
			gfx::Button{SDL_FPoint{400.0f, 280.0f}, std::make_unique<gfx::Text>("How to play", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true},
			gfx::Button{SDL_FPoint{400.0f, 330.0f}, std::make_unique<gfx::Text>("About", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true},
			gfx::Button{SDL_FPoint{400.0f, 380.0f}, std::make_unique<gfx::Text>("Quit", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true}
		};
		
		gfx::SnowScreen snow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};
		const SDL_FRect logoDst{208.0f, 10.0f, 384.0f, 192.0f};

		bool quit{false};
	};
}