#include "MainMenuState.h"
#include "../Game.h"
#include "../GameStates/GameStateManager.h"
#include "../GameStates/CutsceneState.h"
#include "../GameStates/HowToPlayState.h"
#include "../GameStates/AboutState.h"
#include "../AudioCache.h"

#include <SDL_render.h>
#include <SDL_mixer.h>

namespace sus::states
{
	MainMenuState::MainMenuState(Game &game) noexcept
		: game{game}
	{
		Mix_PlayMusic(game.audioCache.getMusic(0), -1);
	}
	
	void MainMenuState::update() noexcept
	{
		if (!quit)
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
				Mix_HaltMusic();

				game.gameStateManager.popBack();
				game.gameStateManager.emplaceBack<states::CutsceneState>(game);
				Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
			}
			else if (buttons[1].wasReleased())
			{
				game.gameStateManager.emplaceBack<states::HowToPlayState>(game);
				Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
			}
			else if (buttons[2].wasReleased())
			{
				game.gameStateManager.emplaceBack<states::AboutState>(game);
				Mix_PlayChannel(-1, game.audioCache.getChunk(5), 0);
			}
			else if (buttons[3].wasReleased())
			{
				quit = true;
				Mix_PlayChannel(0, game.audioCache.getChunk(5), 0);
			}
		}

		if (quit && !Mix_Playing(0))
			game.terminate();

		snow.update();
	}

	void MainMenuState::render() const noexcept
	{
		SDL_Renderer *const renderer{game.getRenderer()};

		SDL_SetRenderDrawColor(renderer, 15, 15, 25, 255);
		SDL_RenderFillRect(renderer, nullptr);

		snow.render(game.getRenderer());

		SDL_RenderCopyF(renderer, game.textureCache[3], nullptr, &logoDst);

		for (const gfx::Button &button : buttons)
			button.render();
	}
}