#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define HEIGHT 5
#define SPEED 25

typedef struct _triangle {
	int mid_x;
	int mid_y;
	int status;
	SDL_Color color;
} Triangle;

typedef struct _origin {
	int x;
	int y;
} Origin;

extern int diameter;
extern const int emptySize;
extern int circles;
extern const SDL_Color textColor;
extern const SDL_Color emptyColor;
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int removeOne;
extern int noneSelected;
extern int held_x, held_y;

#endif