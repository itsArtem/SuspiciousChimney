#include "FontCache.h"

#include <stdexcept>

namespace sus::gfx
{
	TTF_Font *FontCache::open(std::string_view path, int size)
	{
		TTF_Font *const font = TTF_OpenFont(path.data(), size);
		if (!font)
			throw std::runtime_error{SDL_GetError()};
		fonts.emplace_back(font, TTF_CloseFont);
		return font;
	}
}
