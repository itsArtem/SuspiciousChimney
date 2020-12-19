#include "Animation.h"

namespace sus::gfx
{
	Animation::Animation(SDL_Texture *spriteSheet, int frameCount, SDL_Rect start, float timePerFrame, bool loop) noexcept
		: spriteSheet{spriteSheet},
		loop{loop},
		frameCount{frameCount},
		src{start},
		timePerFrame{timePerFrame}
	{
		assert(start.x >= 0 && start.y >= 0 && start.w >= 0 && start.h >= 0 && "Values of start cannot be negative.");
		assert(frameCount >= 0 && "Frame count cannot be negative.");
		assert(timePerFrame >= 0.0f && "Time per frame cannot be negative");
	}

	void Animation::update(int ups) noexcept
	{
		if (!loop && src.x >= end)
			return;

		timePassed += 1000.0f / ups;
		if (timePassed < timePerFrame)
			return;

		timePassed = 0.0f;
		src.x += src.w;
		if (src.x > end)
			src.x = start;
	}

	void Animation::setStart(SDL_Rect src) noexcept
	{
		assert(src.x >= 0 && src.y >= 0 && src.w >= 0 && src.h >= 0 && "Values of start cannot be negative.");
		this->src = src;
		start = src.x;
		end = src.w * (start == 0 ? (frameCount - 1) : frameCount);
	}
}