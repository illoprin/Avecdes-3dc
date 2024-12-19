#ifndef A_CLOCK_H
#define A_CLOCK_H

#include "deps.h"

typedef struct a_Clock {
	double time;
	double deltaTime;
	double fps;
	double lastTime;
} a_Clock;

a_Clock* clockInit();
void clockStart(a_Clock* aclock);
void clockEnd(a_Clock* aclock);
void clockRelease(a_Clock* aclock);

#endif