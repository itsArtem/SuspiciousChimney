#pragma once

#include <SDL_render.h>

namespace sus::gfx
{
	class SnowScreen final
	{
	public:
		SDL_Texture *texture{nullptr};
		SDL_FRect dst{0.0f, 0.0f, 0.0f, 0.0f};
		SDL_FPoint speed{0.0f, 0.0f};

		SnowScreen() = default;
		SnowScreen(SDL_Texture *texture, const SDL_FRect &dst, SDL_FPoint speed) noexcept;

		void update() noexcept;
		void render(SDL_Renderer *renderer, SDL_RendererFlip flip = SDL_FLIP_NONE) const noexcept;

	private:
		SDL_FPoint innerOffset{0.0f, 0.0f};
		SDL_FPoint outerOffset{0.0f, 0.0f};
	};
}