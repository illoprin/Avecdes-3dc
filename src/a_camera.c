#ifndef A_CAMERA_C
#define A_CAMERA_C

#include "a_camera.h"

a_Camera* cameraCreate(a_Program* program, vec3 position, float pitch, float yaw)
{
	a_Camera* camera = (a_Camera*)malloc(sizeof(a_Camera));
	glm_vec3_copy(position, camera->position);
	camera->pitch = pitch;
	camera->yaw = yaw;
	camera->program = program;

	// Init vectors
	glm_vec3_copy(DIR_FORWARD, camera->forward);
	glm_vec3_copy(DIR_RIGHT, camera->right);
	glm_vec3_copy(DIR_UP, camera->up);
	glm_vec3_copy(GLM_VEC3_ZERO, camera->center);
	return camera;
}

void cameraUpdateVectors(a_Camera* camera)
{
	// X
	camera->forward[0] = cosf(glm_rad(camera->yaw)) * cosf(glm_rad(camera->pitch));
	// Y
	camera->forward[1] = sinf(glm_rad(camera->pitch));
	// Z
	camera->forward[2] = cosf(glm_rad(camera->pitch)) * sinf(glm_rad(camera->yaw));

	// Copmpute camera right
	glm_vec3_cross(DIR_UP, camera->forward, camera->right);

	// Compute camera up
	glm_vec3_cross(camera->forward, camera->right, camera->up);

	// Compute center - position vector + forward vector
	glm_vec3_add(camera->position, camera->forward, camera->center);
}

void cameraUpdateMatrices(a_Camera* camera, int* vidmode)
{
	// Compute aspect window_width / window_height
	float aspect = (float)vidmode[0] / (float)vidmode[1];
	// View matrix
	glm_lookat(camera->position, camera->center, camera->up, camera->view);
	// Projection matrix
	glm_perspective(
		glm_rad(CAMERA_FOV_V), aspect, CAMERA_NEAR, CAMERA_FAR, camera->projection
	);
}

void cameraSendToShader(a_Camera* camera)
{
	programSetMatrix4Uniform(camera->program, camera->view, "u_view");
	programSetMatrix4Uniform(camera->program, camera->projection, "u_projection");
}

void cameraUpdate(a_Camera* camera, int* vidmode)
{
	cameraUpdateVectors(camera);
	cameraUpdateMatrices(camera, vidmode);
	cameraSendToShader(camera);
}

void releaseCamera(a_Camera* camera)
{
	if (camera)
		free(camera);
}

#endif