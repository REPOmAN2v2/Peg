#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include "include.h"

void checkCircleClicked(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
int pixelToTriangle(Triangle triangle[][HEIGHT], int *x, int *y);
int distance(int ax, int ay, int bx, int by);
int setEmpty(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
void hold(Triangle triangle[][HEIGHT], int x, int y);
void tryToJumpTo(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
void jumpTo(Triangle triangle[][HEIGHT], Origin origin, int x, int y);
int checkValidAndRemove(Triangle triangle[][HEIGHT], Origin origin, int x, int y);

#endif