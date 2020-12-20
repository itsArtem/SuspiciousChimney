#pragma once

#include <SDL_render.h>
#include "SDL_rect.h"

#include <optional>
#include <cassert>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 26812) // Use of unscoped enum warning. The enum is from an external library, so there's nothing that can be done about it.
#endif

namespace sus::gfx
{
	class Animation final
	{
	public:
		SDL_Texture *spriteSheet{nullptr};
		bool loop{true};

		Animation() = default;
		Animation(SDL_Texture *spriteSheet, int frameCount, SDL_Rect start, float timePerFrame, bool loop) noexcept;

		void update(int ups) noexcept;
		void render(SDL_Renderer *renderer, const SDL_FRect &dst, double angle = 0.0, const std::optional<SDL_FPoint> &centre = {}, SDL_RendererFlip flip = SDL_FLIP_NONE) const noexcept
		{
			SDL_RenderCopyExF(renderer, spriteSheet, &src, &dst, angle, (centre ? &centre.value() : nullptr), flip);
		}

		void setStart(SDL_Rect src) noexcept;

		int getFrameCount() const noexcept { return frameCount; }
		void setFrameCount(int frameCount) noexcept
		{
			assert(frameCount >= 0 && "Frame count cannot be negative.");
			this->frameCount = frameCount;
		}

		float getTimePerFrame() const noexcept { return timePerFrame; }
		void setTimePerFrame(float timePerFrame) noexcept
		{
			assert(timePerFrame > 0.0f && "Time per frame cannot be negative.");
			this->timePerFrame = timePerFrame;
		}

		bool isAtEnd() const noexcept { return src.x >= end; }
		void toBeginning() noexcept { src.x = start; }

	private:
		int frameCount{0};
		SDL_Rect src{0, 0, 0, 0};
		int start{src.x};
		int end{start + src.w * (frameCount - 1)};
		float timePassed{0.0f};
		float timePerFrame{0.0f};
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif