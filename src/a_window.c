#ifndef AVE_WINDOW_C
#define AVE_WINDOW_C

#include "a_window.h"
#include "a_renderer.h"

static void wErrorCallback(int error, const char* desc)
{
	fprintf(stderr, "A_Window Error Callback: %s\nCode: %d\n", desc, error);
}

static void wSizeCallback(GLFWwindow* window, int width, int height)
{
	printf("Window resized: %d %d\n", width, height);
};

extern void wRelease(a_Window* win)
{
	if (win)
	{
		glfwDestroyWindow(win->glfw);
		glfwTerminate();
		lLog(win->logger, "[INFO] Window released\n");
		free(win);
	}
}

static void wCenterWindow(a_Window* win)
{
	/* Get primary monitor resolution */
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    if (mode == NULL) {
        fprintf(stderr, "Window: Failed to get video mode\n");
		wRelease(win);
    }

    /* Get center of screen */
    int pos_x = (mode->width - WIN_WIDTH) / 2;
    int pos_y = (mode->height - WIN_HEIGHT) / 2;

    /* Primary window position - center of screen */
    glfwSetWindowPos(win->glfw, pos_x, pos_y);
}


a_Window* wInit(a_Logger* logger)
{
	a_Window* awin = (a_Window*)malloc(sizeof(a_Window));
	awin->logger = logger;
	awin->title = (char*)malloc(WIN_MAX_TITLE);
	GLFWwindow* window;

	/* Init GLFW Window */
	if (!glfwInit())
	{
		wErrorCallback(-1, "Can't init GLFW\n");
		exit(EXIT_FAILURE);
	}
	
	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, NULL, NULL);
	if (!window)
	{
		wErrorCallback(-1, "Can't create GLFW window. Window pointer is NULL!\n");
		exit(EXIT_FAILURE);
	}
	awin->glfw = window;

	/* Set glfw window hints */
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

	glfwSetErrorCallback(wErrorCallback);
	glfwSetWindowSizeCallback(window, wSizeCallback);
	lLog(awin->logger, "[INFO] Window created with vidmode %d %d\n", WIN_WIDTH, WIN_HEIGHT);

	wCenterWindow(awin);
	return awin;
}

/* Hide and lock cursor */
extern void wToggleGameMode(a_Window* win)
{
	glfwSetInputMode(win->glfw, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
};

/* Set cursor visible */
extern void wToggleSTDMode(a_Window* win)
{
	glfwSetInputMode(win->glfw, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
};

/* Update window variables and pool GLFW events */
extern void wUpdate(a_Window* win)
{
	/* Calculate mouse positions delta */
	glfwGetCursorPos(win->glfw, &win->mouse_x, &win->mouse_y);
	win->mouseDeltaX = win->mouse_x - win->mouse_lx;
	win->mouseDeltaY = win->mouse_y - win->mouse_ly;
	win->mouse_lx = win->mouse_x;
	win->mouse_ly = win->mouse_y;

	glfwPollEvents(); /* Handle events */
}

/* Make OpenGL draw context */
extern void wContext(a_Window* win)
{
	ctxInit(win, 4, 3);
	ctxPrepare();

	lLog(win->logger, "[INFO] OpenGL context created. Version 4.3\n");
}

extern void wTitlef(a_Window* win, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	/* Various string print formatted - ОБОЖАЮ СИ, ОБОЖАЮ ФОНДЮ */
	vsprintf(win->title, format, args);
	va_end(args);
	
	// glfwSetWindowTitle(win->glfw, (const char*)win->title);
}

extern void wStartRender(a_Window* win)
{
	int width, height;
	glfwGetWindowSize(win->glfw, &width, &height);
	// Set OpenGL viewport
	glViewport(0, 0, width, height);
	// Clear context
	ctxClear((vec3){0.1f, 0.1f, 0.145f});
}

extern void wEndRender(a_Window* win)
{
	glfwSwapBuffers(win->glfw);
}

#endif