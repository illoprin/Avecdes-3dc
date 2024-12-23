#include "deps.h"
#include "a_window.h"
#include "a_clock.h"
#include "a_log.h"
#include "a_program.h"
#include "a_bcontroller.h"
#include "a_assets.h"

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
	srand(time(NULL));
	a_Logger* logger = loggerInit(LOG_PATH);
	a_Clock* clock = clockInit();

	window = wInit(logger);
	wContext(window); // Create OpenGL context
	glfwSetKeyCallback(window->glfw, keyCallback);
	glfwSetMouseButtonCallback(window->glfw, mouseButtonCallback);

	// Init assets and OpenGL objects
	a_Mesh* cube_mesh = AssetsGetCubeMesh(logger, (vec3){1.f, 1.f, 1.f});
	a_Program* program = programInit(logger, "a_default.vert", "a_default.frag");

	// Init player controller
	bcontroller = ctlCreate(window, program);
	bcontroller->camera->yaw = 0;
	// Set camera position
	glm_vec3_copy((vec3){0.f, 0.f, -3.f}, bcontroller->camera->position);
	
	/* Init of entities here */
	
	// Entites array
	int entities_count = 10;
	a_Entity* entity_clus[10];
	for (int i = 0; i < entities_count; i++)
	{
		entity_clus[i] = entityCreate(cube_mesh, program, false);
		entitySetPosition(entity_clus[i], 
			(vec3){rand() % 200, rand() % 200, rand() % 200}
		);
		entitySetRotation(entity_clus[i], 
			(vec3){rand() % 90, rand() % 90, rand() % 90}
		);
	};

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
			// entitySetRotation(quad_ent, (vec3){(float)clock->time*100.f, 0.f, (float)clock->time*100.f});
			
			ctlUpdate(bcontroller, (float)clock->deltaTime);
			/* ================================ */
			wStartRender(window); /* Start render: Clear window color */
				programUse(program);
				programSetFloatUniform(program, (float)clock->time, "u_time");
				for (int i = 0; i < entities_count; i++)
				{
					entityRender(entity_clus[i]);
				}
			wEndRender(window); /* End render: Swap buffers */
		clockEnd(clock);
		/* Print current fps */
		// printf("FPS: %.0f", clock->fps);
	}
	/* Clear entities data */
	for (int i = 0; i < entities_count; i++)
	{
		entityRelease(entity_clus[i]);
	};

	/* Clear mesh data */
	meshReleaseAll(cube_mesh);

	/* Clear shader programs */
	programRelease(program);

	/* Release window&clock */
	wRelease(window);
	clockRelease(clock);
	loggerRelease(logger);
	
	return 0;
}