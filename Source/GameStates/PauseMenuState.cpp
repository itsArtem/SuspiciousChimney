#include "PauseMenuState.h"
#include "../GameStates/GameplayState.h"
#include "../GameStates/HowToPlayState.h"
#include "../GameStates/MainMenuState.h"
#include "../AudioCache.h"

#include <SDL_mixer.h>

#include <string>

namespace sus::states
{
	PauseMenuState::PauseMenuState(Game &game) noexcept
		: game{game}
	{
		Mix_PauseMusic();
	}
	
	void PauseMenuState::update() noexcept
	{
		for (gfx::Button &button : buttons)
		{
			if (button.isClicked())
				button.setColourMod({190, 25, 25, 255});
			else if (button.isHoveredOver())
				button.setColourMod({150, 150, 150, 255});
			else
				button.setColourMod({255, 255, 255, 255});
		}

		if (buttons[0].wasReleased())
		{
			game.gameStateManager.popBack();
			
			Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
			Mix_ResumeMusic();
		}
		else if (buttons[1].wasReleased())
		{
			game.gameStateManager.emplaceBack<states::HowToPlayState>(game);
			Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
		}
		else if (buttons[2].wasReleased())
		{
			Mix_HaltMusic();
		
			game.gameStateManager.popBack();
			game.gameStateManager.emplaceBack<states::MainMenuState>(game);
			Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
		}

		snow.update();
	}

	void PauseMenuState::render() const noexcept
	{
		SDL_Renderer *const renderer{game.getRenderer()};

		SDL_SetRenderDrawColor(renderer, 15, 15, 25, 255);
		SDL_RenderFillRect(renderer, nullptr);

		snow.render(game.getRenderer());

		for (const gfx::Button &button : buttons)
			button.render();

		int windowWidth;
		SDL_GetWindowSize(game.getWindow(), &windowWidth, nullptr);

		title.render({windowWidth / 2.0f - title.getSize().x / 2.0f, 40.0f});
	}
}
