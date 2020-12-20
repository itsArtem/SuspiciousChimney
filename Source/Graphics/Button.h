#pragma once

#include "Text.h"

#include <SDL_rect.h>
#include <SDL_mouse.h>

#include <memory>
#include <iostream>

namespace sus::gfx
{
	class Button final
	{
	public:
		SDL_FPoint pos{0.0f, 0.0f};

		Button() = default;
		Button(SDL_FPoint pos, std::unique_ptr<Text> &&text, bool centre) noexcept;

		bool isHoveredOver() const noexcept;
		bool isClicked() const noexcept
		{
			return SDL_GetMouseState(nullptr, nullptr) == SDL_BUTTON_LMASK && isHoveredOver();
		}
		bool wasReleased() noexcept;

		void setText(std::unique_ptr<Text> &&text) noexcept { text = std::move(text); }
		void setColourMod(const SDL_Colour &colour) noexcept { if (text) text->mod = colour; }

		void render() const noexcept { if (text) text->render(pos); }

	private:
		std::unique_ptr<Text> text;
		bool clicked{false};
	};
}