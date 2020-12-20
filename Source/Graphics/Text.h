#pragma once

#include <SDL_render.h>
#include <SDL_pixels.h>
#include <SDL_rect.h>
#include <SDL_ttf.h>

#include <string_view>
#include <memory>
#include <optional>

namespace sus::gfx
{
	class Text final
	{
	public:
		SDL_Colour mod{255, 255, 255, 255};

		Text() = default;
		Text(std::string_view msg, TTF_Font *font, const SDL_Colour &colour, SDL_Renderer *renderer);
		
		void setText(std::string_view msg, TTF_Font *font, const SDL_Colour &colour, SDL_Renderer *renderer);

		void render(const SDL_FPoint &pos, double angle = 0.0, const std::optional<SDL_FPoint> &centre = {}, SDL_RendererFlip flip = SDL_FLIP_NONE) const noexcept;
		const SDL_Point &getSize() const noexcept { return size; }

	private:
		std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture{nullptr, SDL_DestroyTexture};
		SDL_Renderer *renderer{nullptr};
		SDL_Point size{0, 0};

		SDL_Texture *create(std::string_view msg, TTF_Font *font, const SDL_Colour &colour, SDL_Renderer *renderer);
		SDL_Point getSize(std::string_view msg, TTF_Font *font) const noexcept;
	};
}