#include "Game.h"
#include "GameStates/CutsceneState.h"
#include "Utility.h"

#include <SDL_events.h>

#include <chrono>

namespace sus
{
	void Game::run() noexcept
	{
		init();
		running = true;

		using namespace std::chrono;
		steady_clock::time_point lastTime{steady_clock::now()};
		const float timePerFrame{1e9f / ups};
		float delta{0.0f};

		while (running)
		{
			const steady_clock::time_point now{steady_clock::now()};
			delta += (now - lastTime).count() / timePerFrame;
			if (delta > ups * 2.0f) 
				delta = ups * 2.0f;
			lastTime = now;

			while (delta > 0)
			{
				update();
				--delta;
			}

			render();
		}
	}
	
	void Game::init()
	{
		window.reset(SDL_CreateWindow("Suspicious Chimney", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN));
		renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED));

		gameStateManager.emplaceBack<states::CutsceneState>(*this);
	}

	void Game::update() noexcept
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				running = false;

		gameStateManager.update();
	}

	void Game::render() const noexcept
	{
		gameStateManager.render();

		SDL_RenderPresent(renderer.get());
		SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
		SDL_RenderClear(renderer.get());
	}
}
