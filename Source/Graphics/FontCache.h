#pragma once

#include <SDL_ttf.h>

#include <vector>
#include <memory>
#include <string_view>
#include <cassert>

namespace sus::gfx
{
	class FontCache final
	{
	public:
		using SizeType = std::vector<std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>>::size_type;

		TTF_Font *open(std::string_view path, int size);
		void close(SizeType index) noexcept { fonts.erase(fonts.begin() + index); }

		TTF_Font *get(SizeType index) const noexcept
		{
			assert(index < fonts.size() && "Index out of bounds!");
			return fonts[index].get();
		}

		TTF_Font *operator [](SizeType index) const noexcept
		{
			assert(index < fonts.size() && "Index out of bounds!");
			return fonts[index].get();
		}

		SizeType getSize() const noexcept { return fonts.size(); }

	private:
		std::vector<std::unique_ptr<TTF_Font, decltype(&TTF_CloseFont)>> fonts;
	};
}