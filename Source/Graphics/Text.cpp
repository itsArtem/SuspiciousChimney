#include "Text.h"

#include <stdexcept>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 26812)
#endif

namespace sus::gfx
{
	Text::Text(std::string_view msg, TTF_Font *font, const SDL_Colour &colour, SDL_Renderer *renderer)
		: texture{create(msg, font, colour, renderer), SDL_DestroyTexture},
		renderer{renderer},
		size{getSize(msg, font)}
	{
	}

	void Text::setText(std::string_view msg, TTF_Font *font, const SDL_Colour &colour, SDL_Renderer *renderer)
	{
		texture.reset(create(msg, font, colour, renderer));
		TTF_SizeText(font, msg.data(), &size.x, &size.y);
		this->renderer = renderer;
	}

	void Text::render(const SDL_FPoint &pos, double angle, const std::optional<SDL_FPoint> &centre, SDL_RendererFlip flip) const noexcept
	{
		const SDL_FRect dst1{pos.x, pos.y, static_cast<float>(size.x), static_cast<float>(size.y)};
		const SDL_FRect dst2{dst1.x + 1, dst1.y + 1, dst1.w, dst1.h};

		SDL_SetTextureColorMod(texture.get(), 0, 0, 0);
		SDL_RenderCopyExF(renderer, texture.get(), nullptr, &dst2, angle, centre ? &centre.value() : nullptr, flip);
		
		SDL_SetTextureColorMod(texture.get(), mod.r, mod.b, mod.g);
		SDL_SetTextureAlphaMod(texture.get(), mod.a);

		SDL_RenderCopyExF(renderer, texture.get(), nullptr, &dst1, angle, centre ? &centre.value() : nullptr, flip);
	}

	SDL_Texture *Text::create(std::string_view msg, TTF_Font *font, const SDL_Colour &colour, SDL_Renderer *renderer)
	{
		std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> surface{TTF_RenderText_Blended(font, msg.data(), colour), SDL_FreeSurface};
		if (!surface)
			throw std::runtime_error{SDL_GetError()};
		return SDL_CreateTextureFromSurface(renderer, surface.get());
	}

	SDL_Point Text::getSize(std::string_view msg, TTF_Font *font) const noexcept
	{
		SDL_Point size;
		TTF_SizeText(font, msg.data(), &size.x, &size.y);
		return size;
	}
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
