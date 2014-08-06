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
extern int circles;
extern const SDL_Color textColor;
extern const SDL_Color emptyColor;
extern SDL_Window *window;
extern SDL_Renderer *renderer;

void gameplay();
void initialiseGame(Triangle triangle[][HEIGHT], Origin *origin);
void resize(Triangle triangle[][HEIGHT], Origin *origin);
SDL_Color randColor();
void update(float dt, Triangle triangle[][HEIGHT]);
void drawGame(Triangle triangle[][HEIGHT], Origin origin);
void drawText(Triangle triangle[][HEIGHT], SDL_Rect position);
void SDLPrint(int textsize, SDL_Color color, SDL_Rect position, const char *text);
void events(Triangle triangle[][HEIGHT], Origin origin);
void checkCircleClicked(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
int pixelToTriangle(Triangle triangle[][HEIGHT], int *x, int *y);
int distance(int ax, int ay, int bx, int by);
int setEmpty(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
void hold(Triangle triangle[][HEIGHT], int x, int y);
void tryToJumpTo(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
void jumpTo(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
int checkValidAndRemove(Triangle triangle[][HEIGHT], Origin origin, int x, int y);

#endif
