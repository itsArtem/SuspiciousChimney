#include "TextureCache.h"

#include <SDL_image.h>

#include <stdexcept>

namespace sus::gfx
{
	SDL_Texture *TextureCache::load(std::string_view path, SDL_Renderer *renderer)
	{
		SDL_Texture *const texture = IMG_LoadTexture(renderer, path.data());
		if (!texture)
			throw std::runtime_error{SDL_GetError()};
		textures.emplace_back(texture, SDL_DestroyTexture);
		return texture;
	}
}
