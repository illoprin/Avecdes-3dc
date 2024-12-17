
#include "deps.h"
#include "a_window.h"
#include "a_clock.h"
#include "a_log.h"

void keyCallback(
	GLFWwindow* window, 
	int key, 
	int scancode, 
	int action, 
	int mods
)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void mouseButtonCallback(
	GLFWwindow* window, 
	int button, 
	int action, 
	int mods
)
{

}

int main(void)
{
	a_Logger* logger = loggerInit(LOG_PATH);
	a_Clock* clock = clockInit();
	a_Window* window = wInit(logger);
	
	glfwSetKeyCallback(window->glfw, keyCallback);
	glfwSetMouseButtonCallback(window->glfw, mouseButtonCallback);

	wContext(window, 3, 3);
	/*
	 * GameLoop model:
	 * 		Handle Events (keypressed, mousemoved)
	 * 		Check Changes (mouse has been moved, item has been dropped)
	 * 		Update Variables (objects models, camera mvp & etc)
	 * 		Render
	 * 		Swap Buffers (blit rendered image to screen)
	 */
	while (!glfwWindowShouldClose(window->glfw))
	{
		clockStart(clock);
			wUpdate(window);

			wStartRender(window); /* Start render: Clear window color */
				/* TODO: Rendering */
			wEndRender(window); /* End render: Swap buffers */
		clockEnd(clock);
		/* Print current fps */
		// printf("FPS: %.0f", clock->fps);
	}
	/* Clear buffers */

	/* Release window&clock */
	wRelease(window);
	clockRelease(clock);
	loggerRelease(logger);
	
	return 0;
}