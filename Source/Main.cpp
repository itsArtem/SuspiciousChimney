#include "Game.h"
#include "Debug.h"

#include <SDL.h>
#include <SDL_log.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

int main(int argc, char *argv[])
{
	int status{0};
	SUS_DEBUG_CALL(SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0
		|| IMG_Init(IMG_INIT_PNG) == 0
		|| TTF_Init() == -1
		|| Mix_Init(MIX_INIT_OGG) == 0
		|| Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == 1)
		status = 1;
	else
		sus::Game{}.run();

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

	Mix_Quit();
	Mix_CloseAudio();

	return status; 
}