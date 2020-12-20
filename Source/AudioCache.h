#pragma once

#include <SDL_mixer.h>

#include <vector>
#include <memory>
#include <string_view>
#include <cassert>

namespace sus
{
	class AudioCache final
	{
	public:
		using SizeType = std::vector<std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>>::size_type;
		
		void loadMusic(std::string_view path);
		void loadChunk(std::string_view path);

		void removeMusic(SizeType index) noexcept
		{
			assert(index < music.size() && "Index out of bounds!");
			music.erase(music.begin() + index);
		}

		void removeChunk(SizeType index) noexcept
		{
			assert(index < chunks.size() && "Index out of bounds!");
			chunks.erase(chunks.begin() + index);
		}

		Mix_Music *getMusic(SizeType index) const noexcept
		{
			assert(index < music.size() && "Index out of bounds!");
			return music[index].get();
		}
		
		Mix_Chunk *getChunk(SizeType index) const noexcept
		{
			assert(index < chunks.size() && "Index out of bounds!");
			return chunks[index].get();
		}

	private:
		std::vector<std::unique_ptr<Mix_Music, decltype(&Mix_FreeMusic)>> music;
		std::vector<std::unique_ptr<Mix_Chunk, decltype(&Mix_FreeChunk)>> chunks;
	};
}