#include "GameOverState.h"
#include "../GameStates/GameplayState.h"
#include "../GameStates/MainMenuState.h"

#include <string>

namespace sus::states
{
	GameOverState::GameOverState(Game &game, std::int32_t  score, std::int32_t  highscore) noexcept
		: game{game},
		score{std::to_string(score), game.fontCache[2], SDL_Colour{255, 255, 100, 255}, game.getRenderer()},
		highscore{std::to_string(highscore), game.fontCache[2], SDL_Colour{255, 255, 100, 255}, game.getRenderer()}
	{
	}
	
	void GameOverState::update() noexcept
	{
		if (buttons[0].wasReleased())
		{
			game.gameStateManager.popBack();
			game.gameStateManager.emplaceBack<states::GameplayState>(game);
		}
		else if (buttons[1].wasReleased())
		{
			game.gameStateManager.popBack();
			game.gameStateManager.emplaceBack<states::MainMenuState>(game);
		}

		for (gfx::Button &button : buttons)
		{
			if (button.isClicked())
				button.setColourMod({190, 25, 25, 255});
			else if (button.isHoveredOver())
				button.setColourMod({150, 150, 150, 255});
			else
				button.setColourMod({255, 255, 255, 255});
		}

		snow.update();
	}

	void GameOverState::render() const noexcept
	{
		SDL_Renderer *const renderer{game.getRenderer()};

		SDL_SetRenderDrawColor(renderer, 20, 15, 15, 255);
		SDL_RenderFillRect(renderer, nullptr);

		snow.render(game.getRenderer());

		for (const gfx::Button &button : buttons)
			button.render();

		int windowWidth;
		SDL_GetWindowSize(game.getWindow(), &windowWidth, nullptr);

		title.render({windowWidth / 2.0f - title.getSize().x / 2.0f, 40.0f});
		
		scoreMsg.render({windowWidth / 2.0f - scoreMsg.getSize().x / 2.0f, 120.0f});
		score.render({windowWidth / 2.0f - scoreMsg.getSize().x / 2.0f + scoreMsg.getSize().x, 120});

		highscoreMsg.render({windowWidth / 2.0f - highscoreMsg.getSize().x / 2.0f, 120.0f + scoreMsg.getSize().y});
		highscore.render({windowWidth / 2.0f - highscoreMsg.getSize().x / 2.0f + highscoreMsg.getSize().x, 120.0f + scoreMsg.getSize().y});
		
		msg.render({windowWidth / 2.0f - msg.getSize().x / 2.0f, 120.0f + scoreMsg.getSize().y * 3});
	}
}
