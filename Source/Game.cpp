#include "Game.h"
#include "GameStates/MainMenuState.h"
#include "Utility.h"

#include <SDL_events.h>
#include <SDL_ttf.h>

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
		
		textureCache.load("Resources/Textures/SpriteSheet.png", renderer.get());
		textureCache.load("Resources/Textures/Snow.png", renderer.get());
		textureCache.load("Resources/Textures/ChimneyInside.png", renderer.get());
		textureCache.load("Resources/Textures/Logo.png", renderer.get());
		
		fontCache.open("Resources/Font.ttf", 32);
		fontCache.open("Resources/Font.ttf", 42);
		fontCache.open("Resources/Font.ttf", 29);
		fontCache.open("Resources/Font.ttf", 32);

		audioCache.loadChunk("Resources/Audio/Attack.wav");
		audioCache.loadChunk("Resources/Audio/GameOver.wav");
		audioCache.loadChunk("Resources/Audio/Heal.wav");
		audioCache.loadChunk("Resources/Audio/Hit.wav");
		audioCache.loadChunk("Resources/Audio/Hurt.wav");
		audioCache.loadChunk("Resources/Audio/Menu.wav");
		audioCache.loadChunk("Resources/Audio/Orb.wav");
		audioCache.loadChunk("Resources/Audio/SpecialAttack.wav");
		audioCache.loadChunk("Resources/Audio/Hit.wav");
		
		TTF_SetFontStyle(fontCache[0], TTF_STYLE_BOLD);
		TTF_SetFontStyle(fontCache[1], TTF_STYLE_BOLD);
		TTF_SetFontStyle(fontCache[3], TTF_STYLE_BOLD | TTF_STYLE_UNDERLINE);

		gameStateManager.emplaceBack<states::MainMenuState>(*this);
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
