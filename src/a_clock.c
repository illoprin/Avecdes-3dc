#ifndef A_CLOCK_C
#define A_CLOCK_C
#include "a_clock.h"

a_Clock* clockInit()
{
	a_Clock* aclock = (a_Clock*)malloc(sizeof(a_Clock));
	if (aclock != NULL) {
		/* Init zero values */
        memset(aclock, 0, sizeof(a_Clock));
    }
	return aclock;
}

void clockStart(a_Clock* aclock)
{
	aclock->time = glfwGetTime();
}

void clockEnd(a_Clock* aclock)
{
	aclock->lastTime = aclock->time;
	aclock->time = glfwGetTime();
	/* Calc delta time in seconds */
	aclock->deltaTime = (aclock->time - aclock->lastTime);
	aclock->fps = aclock->deltaTime != 0.0 ? 1 / aclock->deltaTime : 999.0;
	/*	Limit fps bad attempt
		if (aclock->deltaTime < 1.0 / MAX_FPS)
		{
			double sleep_time = (1.0 / MAX_FPS) - aclock->deltaTime;
			usleep((int)(sleep_time * 1000000));
		}
	*/
}

void clockRelease(a_Clock* aclock)
{
	if (aclock) free(aclock);
}

#endif