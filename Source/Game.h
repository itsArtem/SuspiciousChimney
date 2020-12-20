#pragma once

#include "GameStates/GameStateManager.h"
#include "Graphics/TextureCache.h"
#include "Graphics/FontCache.h"
#include "AudioCache.h"

#include <SDL_video.h>
#include <SDL_render.h>

#include <memory>

namespace sus
{
	class Game final
	{
	public:
		const int ups{60};
		
		states::GameStateManager gameStateManager;
		
		gfx::TextureCache textureCache;
		gfx::FontCache fontCache;
		AudioCache audioCache;

		void run() noexcept;
		void terminate() noexcept { running = false; }

		SDL_Window *getWindow() const noexcept { return window.get(); }
		SDL_Renderer *getRenderer() const noexcept { return renderer.get(); }

	private:
		std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window{nullptr, SDL_DestroyWindow};
		std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer{nullptr, SDL_DestroyRenderer};
		bool running{false};

		void init();
		
		void update() noexcept;
		void render() const noexcept;
	};
}