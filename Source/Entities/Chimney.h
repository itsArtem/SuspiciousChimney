#pragma once

#include "Entity.h"

#include <SDL_render.h>
#include <SDL_rect.h>

namespace sus::scene
{
	class Camera;
}

namespace sus::entities
{
	class Chimney final : public Entity
	{
	public:
		Chimney(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &cellSrc, SDL_Rect &tipSrc, const scene::Camera &camera, int length, const SDL_FPoint &tipSize) noexcept;

		void render(SDL_Renderer *renderer) const noexcept override;
		
	private:
		SDL_Texture *texture;
		const SDL_Rect cellSrc;
		const SDL_Rect tipSrc;
		const scene::Camera &camera;

		const int length;
		const SDL_FPoint tipSize;
	};
}