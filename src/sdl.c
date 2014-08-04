#include "sdl.h"

int initialiseSDL()
{
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		fprintf(stderr, "Failed to initialise SDL (%s)\n", SDL_GetError());
		return -1;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		fprintf(stderr, "Failed to initialise linear texture rendering");
	}

	window = SDL_CreateWindow("Peg",SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									700,
									700,
									SDL_WINDOW_SHOWN);

	if (window == NULL) {
		fprintf(stderr, "Failed to create the window: (%s)\n", SDL_GetError());
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		fprintf(stderr, "Failed to initialise renderer: (%s)\n", SDL_GetError());
		return -1;
	}

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int initted = IMG_Init(IMG_INIT_PNG);

	if ((initted&IMG_INIT_PNG) != IMG_INIT_PNG) {
		fprintf(stderr, "Failed to initialise PNG support (%s)\n", IMG_GetError());
		return -1;
	}

/*	initted = Mix_Init(MIX_INIT_MP3);
	if ((initted&MIX_INIT_MP3) != MIX_INIT_MP3) {
		fprintf(stdout, "Mix_Init: Failed to init MP3 support! (%s)\n", Mix_GetError());
    	return -1;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		fprintf(stderr, "Failed to initialise SDL_mixer (%s)\n", Mix_GetError());
		return -1;
	}*/

	if (TTF_Init() == -1) {
		fprintf(stderr, "Failed to initialise SDL_TTF (%s)\n", TTF_GetError());
		return -1;
	}

	fprintf(stdout, "DEBUG: Finished initialising SDL.\n");
	
    return 0;
} 