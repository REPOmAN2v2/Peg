#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#define HEIGHT 5
#define SPEED 25

typedef struct _color {
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} Color;

typedef struct _triangle {
	int act_x;
	int act_y;
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
extern int emptySize;
extern const int circles;
extern const SDL_Color textColor;
extern const SDL_Color emptyColor;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

void gameplay();
Triangle ** initialiseGame(Origin *origin);
void resize(Triangle **triangle, Origin *origin);
SDL_Color randColor();
void drawGame(Triangle **triangle, int held_y, int held_x, int numCircles, int noneSelected, Origin origin);
void SDLPrint(int textsize, SDL_Color color, SDL_Rect position, const char *text);
int drawCircle(Sint16 x, Sint16 y, Sint16 rad, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
int drawLine(Sint16 x1, Sint16 x2, Sint16 y);

#endif