#pragma once

#include "GameStates/GameStateManager.h"

#include <SDL_video.h>
#include <SDL_render.h>

#include <memory>

namespace sus
{
	class Game final
	{
	public:
		const int ups{60};

		void run() noexcept;
		void terminate() noexcept { running = false; }

	private:
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
		std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};
		bool running{false};

		states::GameStateManager gameStateManager;

		void init();
		
		void update() noexcept;
		void render() const noexcept;
	};
}