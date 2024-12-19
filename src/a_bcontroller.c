#ifndef A_BCONTROLLER_C
#define A_BCONTROLLER_C

#include "a_bcontroller.h"


a_BasicController* ctlCreate(a_Window* window, a_Program* program)
{
	a_Camera* camera = cameraCreate(program, (vec3)GLM_VEC3_ZERO_INIT, 0.f, 0.f);
	a_BasicController* ctl = (a_BasicController*)malloc(sizeof(a_BasicController));
	ctl->camera = camera;
	ctl->window = window;
	wToggleGameMode(window);
	ctl->isGameMode = true;
	return ctl;
}

static void ctlUpdateStates(a_BasicController* ctl)
{
	ctl->states[PL_M_FORWARD] = glfwGetKey(ctl->window->glfw, GLFW_KEY_W);
	ctl->states[PL_M_BACKWARD] = glfwGetKey(ctl->window->glfw, GLFW_KEY_S);
	ctl->states[PL_M_LEFT] = glfwGetKey(ctl->window->glfw, GLFW_KEY_A);
	ctl->states[PL_M_RIGHT] = glfwGetKey(ctl->window->glfw, GLFW_KEY_D);
	ctl->states[PL_W_FOCUS] = glfwGetKey(ctl->window->glfw, GLFW_KEY_TAB);
}

static void ctlHandleKeyboardEvents(a_BasicController* ctl, float deltaTime)
{
	a_Camera* cam = ctl->camera;
	int* states = ctl->states;
	
	// Movement vectors
	vec3 f_vel; // Forward velocity vector
	glm_vec3_copy(cam->forward, f_vel);
	glm_vec3_scale_as(f_vel, PLAYER_SPEED * deltaTime, f_vel);
	
	vec3 r_vel; // Right velocity vector
	glm_vec3_copy(cam->right, r_vel);
	glm_vec3_scale_as(r_vel, PLAYER_SPEED * deltaTime, r_vel);

	if (states[PL_M_FORWARD] == GLFW_PRESS)
		glm_vec3_add(cam->position, f_vel, cam->position);
	if (states[PL_M_BACKWARD] == GLFW_PRESS)
		glm_vec3_sub(cam->position, f_vel, cam->position);
	if (states[PL_M_LEFT] == GLFW_PRESS)
		glm_vec3_add(cam->position, r_vel, cam->position);
	if (states[PL_M_RIGHT] == GLFW_PRESS)
		glm_vec3_sub(cam->position, r_vel, cam->position);
}

static void ctlHandleMouseEvents(a_BasicController* ctl, float deltaTime)
{
	a_Camera* cam = ctl->camera;
	a_Window* win = ctl->window;
	cam->pitch -= (win->mouseDeltaY * PLAYER_SENSITIVITY * deltaTime);
	cam->pitch = glm_clamp(cam->pitch, -90.f, 90.f);
	cam->yaw += win->mouseDeltaX * PLAYER_SENSITIVITY * deltaTime;
}

void ctlUpdate(a_BasicController* ctl, float deltaTime)
{
	// Get current window size for camera update function
	int vidmode[2];
	glfwGetWindowSize(ctl->window->glfw, &vidmode[0], &vidmode[1]);

	// Update controller states
	ctlUpdateStates(ctl);

	if (ctl->isGameMode)
	{
		// Handle events
		ctlHandleKeyboardEvents(ctl, deltaTime);
		ctlHandleMouseEvents(ctl, deltaTime);
	}
	// Update camera
	cameraUpdate(ctl->camera, vidmode);
}

void ctlRelease(a_BasicController* ctl)
{
	if (ctl)
	{
		if (ctl->camera) free(ctl->camera);
		free(ctl);
	}
}

#endif