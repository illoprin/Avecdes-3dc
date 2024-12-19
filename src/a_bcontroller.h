#ifndef A_BCONTROLLER_H
#define A_BCONTROLLER_H

#include "deps.h"
#include "a_window.h"
#include "a_camera.h"

typedef struct a_BasicController {
	a_Camera* camera;
	a_Window* window;
	bool isGameMode;
	int states[5];	
} a_BasicController;

a_BasicController* ctlCreate(a_Window* window, a_Program* program);
void ctlUpdate(a_BasicController* controller, float deltaTime);
void ctlRelease(a_BasicController* controller);


#endif