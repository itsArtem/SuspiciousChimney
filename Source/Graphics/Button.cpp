#include "Button.h"
#include "../Utility.h"

namespace sus::gfx
{
	Button::Button(SDL_FPoint pos, std::unique_ptr<Text> &&text, bool centre) noexcept
		: pos{!centre ? pos : SDL_FPoint{pos.x - text->getSize().x / 2, pos.y - text->getSize().y / 2}},
		text{std::move(text)}
	{
	}
	
	bool Button::isHoveredOver() const noexcept
	{
		if (!text)
			return false;

		const SDL_FRect bounds{pos.x, pos.y, static_cast<float>(text->getSize().x), static_cast<float>(text->getSize().y)};
		SDL_Point mouse;

		SDL_GetMouseState(&mouse.x, &mouse.y);
		return isPointInRect({static_cast<float>(mouse.x), static_cast<float>(mouse.y)}, bounds);
	}
	
	bool Button::wasReleased() noexcept
	{
		if (isClicked())
		{
			clicked = true;
			return false;
		}
		else if (clicked && isHoveredOver())
		{
			clicked = false;
			return true;
		}

		clicked = false;
		return false;
	}
}
