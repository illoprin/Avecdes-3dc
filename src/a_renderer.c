#ifndef A_RENDERER_C
#define A_RENDERER_C

#include "a_renderer.h"

extern void ctxInit(a_Window* win, char maj, char min)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, maj);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwMakeContextCurrent(win->glfw);
	/* Enable VSync */
	glfwSwapInterval(1); /* Creates window motion slowdown on X11 */

	/* Init GLEW - OpenGL >3.0 functions */
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Could not initialize GLEW\n");
		exit(EXIT_FAILURE);
	}
	glewExperimental = true;
}

extern void ctxPrepare()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glCullFace(GL_CCW);
	printf("OpenGL parametres inited\n");
}

extern void ctxClear(vec3 rgba)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(rgba[0], rgba[1], rgba[2], 1.0f);
}


#endif