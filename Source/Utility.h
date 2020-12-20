#pragma once

#include <SDL_rect.h>

namespace sus
{
	inline bool hasIntersection(const SDL_FRect &first, const SDL_FRect &second) noexcept
	{
		return !(first.x + first.w < second.x || first.y + first.h < second.y || first.x > second.x + second.w || first.y > second.y + second.h);
	}

	inline bool isPointInRect(const SDL_FPoint &point, const SDL_FRect &rect) noexcept
	{
		return !(point.x < rect.x || point.x > rect.x + rect.w || point.y < rect.y || point.y > rect.y + rect.h);
	}
}