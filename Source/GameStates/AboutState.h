#pragma once

#include "GameState.h"
#include "../Game.h"
#include "../Graphics/SnowScreen.h"
#include "../Graphics/Button.h"
#include "../Graphics/Text.h"

#include <SDL_rect.h>

namespace sus::states
{
	class AboutState final : public GameState
	{
	public:
		AboutState(Game &game) noexcept
			: game{game} { }

		void update() noexcept override;
		void render() const noexcept override;

	private:
		Game &game;

		gfx::SnowScreen snow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};
		gfx::Button back{SDL_FPoint{35.0f, 45.0f}, std::make_unique<gfx::Text>("Back", game.fontCache[3], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), false};

		gfx::Text title{"About", game.fontCache[1], SDL_Colour{200, 30, 30, 255}, game.getRenderer()};
		gfx::Text msg1{"Suspicious Chimney is a game developed in 48 hours", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text msg2{"from scratch using C++ and SDL2 by Artem Katerynych", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text msg3{"for a Christmas coding challenge.", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text msg4{"Thanks for playing!", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text msg5{"December 20, 2020", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
	};
}