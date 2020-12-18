#pragma once

#include <SDL_render.h>

#include <vector>
#include <memory>
#include <string_view>
#include <cassert>

namespace sus::gfx
{
	class TextureCache final
	{
	public:
		using SizeType = std::vector<std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>>::size_type;

		SDL_Texture *load(std::string_view path, SDL_Renderer *renderer);
		void remove(SizeType index) noexcept { textures.erase(textures.begin() + index); }

		SDL_Texture *get(SizeType index) const noexcept
		{
			assert(index < textures.size() && "Index out of bounds!");
			return textures[index].get();
		}

		SDL_Texture *operator [](SizeType index) const noexcept
		{
			assert(index < textures.size() && "Index out of bounds!");
			return textures[index].get();
		}

		SizeType getSize() const noexcept { return textures.size(); }

	private:
		std::vector<std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>> textures;
	};
}