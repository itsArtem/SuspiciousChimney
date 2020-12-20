#include "AudioCache.h"

#include <stdexcept>

namespace sus
{
	void AudioCache::loadMusic(std::string_view path)
	{
		Mix_Music *const sample{Mix_LoadMUS(path.data())};
		if (!sample)
			throw std::runtime_error{SDL_GetError()};
		music.emplace_back(sample, Mix_FreeMusic);
	}

	void AudioCache::loadChunk(std::string_view path)
	{
		Mix_Chunk *const sample{Mix_LoadWAV(path.data())};
		if (!sample)
			throw std::runtime_error{SDL_GetError()};
		chunks.emplace_back(sample, Mix_FreeChunk);
	}
}
