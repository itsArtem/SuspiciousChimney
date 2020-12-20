#include "MainMenuState.h"
#include "../Game.h"
#include "../GameStates/GameStateManager.h"
#include "../GameStates/CutsceneState.h"
#include "../GameStates/HowToPlayState.h"
#include "../GameStates/AboutState.h"

#include <SDL_render.h>

namespace sus::states
{
	void MainMenuState::update() noexcept
	{
		if (buttons[0].wasReleased())
		{
			game.gameStateManager.popBack();
			game.gameStateManager.emplaceBack<states::CutsceneState>(game);
		}
		else if (buttons[1].wasReleased())
		{
			game.gameStateManager.emplaceBack<states::HowToPlayState>(game);
		}
		else if (buttons[2].wasReleased())
		{
			game.gameStateManager.emplaceBack<states::AboutState>(game);
		}
		else if (buttons[3].wasReleased())
			game.terminate();

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