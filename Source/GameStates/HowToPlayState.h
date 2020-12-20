#pragma once

#include "GameState.h"
#include "../Game.h"
#include "../Graphics/Button.h"
#include "../Graphics/SnowScreen.h"
#include "../Graphics/Text.h"
#include "../Graphics/Animation.h"

#include <SDL_pixels.h>
#include <SDL_rect.h>

namespace sus::states
{
	class HowToPlayState final : public GameState
	{
	public:
		HowToPlayState(Game &game) noexcept
			: game{game} { }

		void update() noexcept override;
		void render() const noexcept override;

	private:
		Game &game;

		gfx::SnowScreen snow{game.textureCache[1], {0.0f, 0.0f, 1600.0f, 1600.0f}, {0.01f, 1.3f}};
		gfx::Text title{"How to play", game.fontCache[1], SDL_Colour{200, 30, 30, 255}, game.getRenderer()};

		gfx::Button back{SDL_FPoint{35.0f, 45.0f}, std::make_unique<gfx::Text>("Back", game.fontCache[3], SDL_Colour{255, 255, 255, 255}, game.getRenderer()), false};

		gfx::Animation santa{game.textureCache[0], 2, {32, 0, 16, 24}, 250.0f, true};
		gfx::Animation monster{game.textureCache[0], 3, {48, 40, 24, 32}, 200.0f, true};

		const SDL_Rect candyCaneSrc{120, 48, 8, 8};
		const SDL_Rect specialSrc{120, 40, 8, 8};

		const SDL_Rect specialMetreSrc{8, 128, 128, 8};
		const SDL_Rect specialIconSrc{0, 128, 8, 8};
		float metreProgress{0.0f};

		gfx::Text santaMsg1{"This is Santa. Santa avoids obstacles with A and D", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text santaMsg2{"or the arrow keys. When Santa gets a little angry,", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text santaMsg3{"he attacks with Space or F.", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		
		gfx::Text monsterMsg1{"This is monster. Santa must avoid traps and", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text monsterMsg2{"monsters. Stanta starts with four health levels.", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text monsterMsg3{"If monster hits Santa, Santa loses a health (omg!).", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text monsterMsg4{"Monsters are mean.", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};

		gfx::Text candyCaneMsg{"This is candy cane. Candy cane heals Santa.", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		
		gfx::Text specialMsg1{"This is magic orbs. Magic orbs refill Santa's", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text specialMsg2{"special metre.", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};

		gfx::Text specialMetreMsg1{"This is special metre. When metre fills up, santa holds", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
		gfx::Text specialMetreMsg2{"S to to increase his attack strength.", game.fontCache[2], SDL_Colour{255, 255, 255, 255}, game.getRenderer()};
	};
}