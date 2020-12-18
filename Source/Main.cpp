#include "Game.h"
#include "Debug.h"

#include <SDL.h>
#include <SDL_log.h>
#include <SDL_image.h>

int main(int argc, char *argv[])
{
	int status{0};
	SUS_DEBUG_CALL(SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE));

	if (SDL_Init(SDL_INIT_VIDEO) < 0 || IMG_Init(IMG_INIT_PNG) == 0)
		status = 1;
	else
		sus::Game{}.run();

	SDL_Quit();
	IMG_Quit();

	return status; 
}