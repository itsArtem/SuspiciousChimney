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
	class GameOverState final : public GameState
	{
	public:
		GameOverState(Game &game, std::int32_t  score, std::int32_t  highscore) noexcept;

		void update() noexcept override;
		void render() const noexcept override;

	private:
		Game &game;
		std::array<gfx::Button, 2> buttons{
			gfx::Button{SDL_FPoint{400.0f, 280.0f}, std::make_unique<gfx::Text>("Retry", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true},
			gfx::Button{SDL_FPoint{400.0f, 320.0f}, std::make_unique<gfx::Text>("Main Menu", game.fontCache[0], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), true},
		};

		gfx::SnowScreen snow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};

		gfx::Text title{"Game Over", game.fontCache[1], SDL_Colour{200, 30, 30, 255}, game.getRenderer()};
		gfx::Text scoreMsg{"Score: ", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text score;

		gfx::Text highscoreMsg{"Highscore: ", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text highscore;

		gfx::Text msg{"Santa will be back for revenge!", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
	};
}