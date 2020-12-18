#pragma once

#include <SDL_rect.h>

namespace sus
{
	inline bool hasIntersection(const SDL_FRect &first, const SDL_FRect &second) noexcept
	{
		return !(first.x + first.w < second.x || first.y + first.h < second.y || first.x > second.x + second.w || first.y > second.y + second.h);
	}
}