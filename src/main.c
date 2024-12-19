#include "deps.h"
#include "a_window.h"
#include "a_clock.h"
#include "a_log.h"
#include "game_object/a_mesh.h"
#include "a_program.h"
#include "a_bcontroller.h"

a_Window* window = NULL;
a_BasicController* bcontroller = NULL;

void keyCallback(
	GLFWwindow* glfw, 
	int key, 
	int scancode, 
	int action, 
	int mods
)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(glfw, GLFW_TRUE);

		if (window)
		{
			if (key == GLFW_KEY_TAB && bcontroller)
			{
				if (bcontroller->isGameMode == true)
				{
					wToggleSTDMode(window);
					bcontroller->isGameMode = false;
				}
				else
				{
					wToggleGameMode(bcontroller->window);
					bcontroller->isGameMode = true;
				}
			}
		}
		
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

int main(int argc, char* argv[])
{
	a_Logger* logger = loggerInit(LOG_PATH);
	a_Clock* clock = clockInit();
	window = wInit(logger);

	glfwSetKeyCallback(window->glfw, keyCallback);
	glfwSetMouseButtonCallback(window->glfw, mouseButtonCallback);

	wContext(window); // Create OpenGL context

	struct Triangle tris = 
	{
		{
			{-0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 0.f},
			{0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 0.f},
			{0.0f, 0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 0.f}
		}
	};
	a_Mesh* triangle_mesh = meshInit(logger, "hello_triangle", &tris, 9);
	// Init vao of triangle mesh
	initVAO(triangle_mesh);

	a_Program* program = programInit(logger, "a_default.vert", "a_default.frag");

	bcontroller = ctlCreate(window, program);

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
			/* ============ Update ============ */
			ctlUpdate(bcontroller, (float)clock->deltaTime);
			/* ================================ */
			wStartRender(window); /* Start render: Clear window color */
				programUse(program);
				programSetFloatUniform(program, (float)clock->time, "u_time");
				renderMesh(triangle_mesh);
				/* TODO: Rendering */
			wEndRender(window); /* End render: Swap buffers */
		clockEnd(clock);
		/* Print current fps */
		// printf("FPS: %.0f", clock->fps);
	}
	/* Clear buffers */
	meshRelease(triangle_mesh);

	/* Clear shader programs */
	programRelease(program);

	/* Release window&clock */
	wRelease(window);
	clockRelease(clock);
	loggerRelease(logger);
	
	return 0;
}