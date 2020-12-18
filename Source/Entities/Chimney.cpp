#include "Chimney.h"

namespace sus::entities
{
	Chimney::Chimney(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &cellSrc, SDL_Rect &tipSrc, const scene::Camera &camera, int length, const SDL_FPoint &tipSize) noexcept
		: Entity{pos, {128.0f, 96.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, -96.0f * (length - 1) - tipSize.y, 128.0f, 96.0f * length + tipSize.y}, camera},
		texture{texture},
		cellSrc{cellSrc},
		tipSrc{tipSrc},
		camera{camera},
		length{length},
		tipSize{tipSize}
	{
	}

	void Chimney::render(SDL_Renderer *renderer) const noexcept
	{
		const SDL_FRect dst{getDestination()};

		for (int i = 0; i < length; ++i)
		{
			const SDL_FRect offsetedDst{dst.x, dst.y - dst.h * i, dst.w, dst.h};
			SDL_RenderCopyF(renderer, texture, &cellSrc, &offsetedDst);
		}

		const SDL_FRect offsetedDst{dst.x, dst.y - dst.h * (length - 1) - tipSize.y, tipSize.x, tipSize.y};
		SDL_RenderCopyF(renderer, texture, &tipSrc, &offsetedDst);
	}
}
