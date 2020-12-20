#include "HowToPlayState.h"
#include "../GameStates/GameStateManager.h"

#include <SDL_video.h>

#include <cmath>

namespace sus::states
{
    void HowToPlayState::update() noexcept
    {
        snow.update();
        
        if (back.isClicked())
            back.setColourMod({190, 25, 25, 255});
        else if (back.isHoveredOver())
            back.setColourMod({150, 150, 150, 255});
        else
            back.setColourMod({255, 255, 255, 255});

        if (back.wasReleased())
            game.gameStateManager.popBack();

        santa.update(game.ups);
        monster.update(game.ups);

        metreProgress += 0.02f;
        if (metreProgress >= 360.0f)
            metreProgress = 0.0f;
    }

    void HowToPlayState::render() const noexcept
    {
        SDL_Renderer *const renderer{game.getRenderer()};

        SDL_SetRenderDrawColor(renderer, 15, 15, 25, 255);
        SDL_RenderFillRect(renderer, nullptr);

        snow.render(renderer);
        back.render();

        int windowWidth;
        SDL_GetWindowSize(game.getWindow(), &windowWidth, nullptr);

        title.render({windowWidth / 2.0f - title.getSize().x / 2.0f, 40.0f});

        santa.render(renderer, {30.0f, 100.0f, 64.0f, 80.0f});
        monster.render(renderer, {22.0f, 190.0f, 80.0f, 128.0f});

        const SDL_FRect candyCaneDst{40.0f, 335.0f, 38.0f, 56.0f};
        SDL_RenderCopyF(renderer, game.textureCache[0], &candyCaneSrc, &candyCaneDst);

        const SDL_FRect specialDst{35.0f, 410.0f, 48.0f, 48.0f};
        SDL_RenderCopyF(renderer, game.textureCache[0], &specialSrc, &specialDst);
        
        const SDL_FRect specialMetreDst{50.0f, 475.0f, 700.0f, 32.0f};
        SDL_RenderCopyF(renderer, game.textureCache[0], &specialMetreSrc, &specialMetreDst);

        const SDL_FRect specialIconDst{(50.0f + specialMetreDst.w / 2 - 16.0f) - std::cos(metreProgress) * (specialMetreDst.w / 2), 475.0f, 32.0f, 32.0f};
        SDL_RenderCopyF(renderer, game.textureCache[0], &specialIconSrc, &specialIconDst);

        santaMsg1.render({120.0f, 100.0f});
        santaMsg2.render({120.0f, 100.0f + santaMsg1.getSize().y});
        santaMsg3.render({120.0f, 100.0f + santaMsg1.getSize().y * 2});

        monsterMsg1.render({120.0f, 200.0f});
        monsterMsg2.render({120.0f, 200.0f + monsterMsg1.getSize().y});
        monsterMsg3.render({120.0f, 200.0f + monsterMsg1.getSize().y * 2});
        monsterMsg4.render({120.0f, 200.0f + monsterMsg1.getSize().y * 3});

        candyCaneMsg.render({120.0f, 350.0f});
        
        specialMsg1.render({120.0f, 410.0f});
        specialMsg2.render({120.0f, 410.0f + specialMsg1.getSize().y});

        specialMetreMsg1.render({50.0f, 520.0f});
        specialMetreMsg2.render({50.0f, 520.0f + specialMetreMsg1.getSize().y});
    }
}