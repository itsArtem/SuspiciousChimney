#include "AboutState.h"
#include "../Game.h"
#include "../GameStates/GameStateManager.h"
#include "../GameStates/CutsceneState.h"

#include <SDL_video.h>

namespace sus::states
{
    void AboutState::update() noexcept
    {
        if (back.isClicked())
            back.setColourMod({190, 25, 25, 255});
        else if (back.isHoveredOver())
            back.setColourMod({150, 150, 150, 255});
        else
            back.setColourMod({255, 255, 255, 255});

        if (back.wasReleased())
            game.gameStateManager.popBack();

        snow.update();
    }

    void AboutState::render() const noexcept
    {
        SDL_Renderer *const renderer{game.getRenderer()};

        SDL_SetRenderDrawColor(renderer, 15, 15, 25, 255);
        SDL_RenderFillRect(renderer, nullptr);

        snow.render(renderer);
        back.render();

        int windowWidth;
        SDL_GetWindowSize(game.getWindow(), &windowWidth, nullptr);

        title.render({windowWidth / 2.0f - title.getSize().x / 2.0f, 40.0f});
        msg1.render({50.0f, 120.0f});
        msg2.render({50.0f, 120.0f + msg1.getSize().y});
        msg3.render({50.0f, 120.0f + msg1.getSize().y * 2});
        msg4.render({50.0f, 120.0f + msg1.getSize().y * 4});
        msg5.render({50.0f, 120.0f + msg1.getSize().y * 5 + 8});
    }
}