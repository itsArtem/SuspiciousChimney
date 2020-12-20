#include "Roof.h"

namespace sus::entities
{
	Roof::Roof(const SDL_FPoint &pos, SDL_Texture *texture, const SDL_Rect &src, const scene::Camera &camera) noexcept
		: Entity{{pos, {800.0f, 267.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, {0.0f, 15.0f, 800.0f, 252.0f}}, {false, ConsumableType::none, {}}, camera},
		texture{texture},
		src{src}
	{
	}
}
