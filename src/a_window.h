#ifndef AVE_WINDOW_H
#define AVE_WINDOW_H

#include "deps.h"
#include "a_log.h"

typedef void (*a_KeyInput)(int key, int action);
typedef void (*a_Mouse)(int button, int action, int mods);




typedef struct a_Window {
	GLFWwindow* glfw;
	/* Mouse vecs */
	double
		mouse_x, mouse_y,
		mouse_lx, mouse_ly,
		mouseDeltaX, mouseDeltaY;
	/* Title */
	char* title;

	a_Logger* logger;
} a_Window;

/* Init new window instance */
a_Window* wInit(a_Logger* logger);
extern void wRelease(a_Window* win);

/* Input */

/* Hide and lock cursor */
extern void wToggleGameMode(a_Window* win);

/* Set cursor visible */
extern void wToggleSTDMode(a_Window* win);

/* Create OpenGL Context */
extern void wContext(a_Window* win);

/* Update window variables */
extern void wUpdate(a_Window* win);

/* Clear screen */
extern void wStartRender(a_Window* win);
/* Swap buffers */
extern void wEndRender(a_Window* win);

/* Set formatted window title */
// extern void wTitlef(a_Window* win, const char* format, ...);

#endif