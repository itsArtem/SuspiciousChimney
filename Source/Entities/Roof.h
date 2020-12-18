#pragma once

#include "Entitiy.h"

#include <SDL_render.h>
#include <SDL_rect.h>

namespace sus::scene
{
	class Camera;
}

namespace sus::entities
{
	class Roof final : public Entity
	{
	public:
		Roof(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override
		{
			SDL_RenderCopyF(renderer, texture, &src, &getDestination());
		}

	private:
		SDL_Texture *texture;
		SDL_Rect src;
	};
}