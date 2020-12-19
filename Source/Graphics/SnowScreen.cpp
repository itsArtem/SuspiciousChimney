#include "SnowScreen.h"

#include <cmath>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 26812) // Use of unscoped enum warning. The enum is from an external library, so there's nothing that can be done about it.
#endif

namespace sus::gfx
{
	SnowScreen::SnowScreen(SDL_Texture *texture, const SDL_FRect &dst, SDL_FPoint speed) noexcept
		: texture{texture},
		dst{dst},
		speed{speed}
	{
	}

	void SnowScreen::update() noexcept
	{
		constexpr float outerMultiplier{1.2f};

		innerOffset.x += speed.x;
		innerOffset.y += speed.y;
	
		if (innerOffset.x > 360.0f)
			innerOffset.x = 0.0f;
		if (innerOffset.y > dst.x + dst.h)
			innerOffset.y = 0.0f;

		outerOffset.x += speed.x * outerMultiplier;
		outerOffset.y += speed.y * outerMultiplier;

		if (outerOffset.x > 360.0f)
			outerOffset.x = 0.0f;
		if (outerOffset.y > dst.x + dst.h / 2)
			outerOffset.y = 0.0f;
	}

	void SnowScreen::render(SDL_Renderer *renderer, SDL_RendererFlip flip) const noexcept
	{
		const SDL_FRect dst1{(dst.x - dst.w / 2) + std::cos(innerOffset.x) * 50, dst.y + innerOffset.y, dst.w, dst.h};
		const SDL_FRect dst2{(dst.x + dst.w / 2) + std::cos(innerOffset.x) * 50, dst.y + innerOffset.y, dst.w, dst.h};
		const SDL_FRect dst3{(dst.x - dst.w / 2) + std::cos(innerOffset.x) * 50, (dst.y - dst.h) + innerOffset.y, dst.w, dst.h};
		const SDL_FRect dst4{(dst.x + dst.w / 2) + std::cos(innerOffset.x) * 50, (dst.y - dst.h) + innerOffset.y, dst.w, dst.h};

		SDL_RenderCopyExF(renderer, texture, nullptr, &dst1, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst2, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst3, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst4, 0.0, nullptr, flip);

		const SDL_FRect dst5{(dst.x + dst.w / 3) - std::cos(outerOffset.x) * 50, dst.y + outerOffset.y, dst.w / 1.5f, dst.h / 1.5f};
		const SDL_FRect dst6{(dst.x - dst.w / 3) - std::cos(outerOffset.x) * 50, dst.y + outerOffset.y, dst.w / 1.5f, dst.h / 1.5f};
		const SDL_FRect dst7{(dst.x + dst.w / 3) - std::cos(outerOffset.x) * 50, (dst.y - dst.h / 2) + outerOffset.y, dst.w / 1.5f, dst.h / 1.5f};
		const SDL_FRect dst8{(dst.x - dst.w / 3) - std::cos(outerOffset.x) * 50, (dst.y - dst.h / 2) + outerOffset.y, dst.w / 1.5f, dst.h / 1.5f};
		const SDL_FRect dst9{(dst.x + dst.w / 3) - std::cos(outerOffset.x) * 50, (dst.y - dst.h) + outerOffset.y, dst.w / 1.5f, dst.h / 1.5f};
		const SDL_FRect dst10{(dst.x - dst.w / 3) - std::cos(outerOffset.x) * 50, (dst.y - dst.h) + outerOffset.y, dst.w / 1.5f, dst.h / 1.5f};

		SDL_RenderCopyExF(renderer, texture, nullptr, &dst5, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst6, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst7, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst8, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst9, 0.0, nullptr, flip);
		SDL_RenderCopyExF(renderer, texture, nullptr, &dst10, 0.0, nullptr, flip);
	}
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif