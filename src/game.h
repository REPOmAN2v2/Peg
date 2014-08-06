#ifndef GAME_H_
#define GAME_H_

#include "include.h"

void gameplay(Triangle triangle[][HEIGHT], Origin origin);
void initialiseGame(Triangle triangle[][HEIGHT], Origin *origin);
void resize(Triangle triangle[][HEIGHT], Origin *origin);
SDL_Color randColor();
int events(Triangle triangle[][HEIGHT], Origin origin);

#endif