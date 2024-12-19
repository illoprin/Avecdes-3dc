#ifndef A_CAMERA_H
#define A_CAMERA_H

#include "deps.h"
#include "a_program.h"

/*
 * Camera struct
 * Stores data about the current projection of the scene projected on local screen coordinates
 * !Has no any movement control
*/
typedef struct a_Camera {
	/* Pointer to current shader program */
	a_Program* program;

	/* Perspective matrix - takes into account fov and aspect */
	mat4 projection;
	/* View matrix - takes into account camera posititon and camera help vectors */
	mat4 view;

	/* Camera global coordinates */
	vec3 position;
	float pitch;
	float yaw;

	/* Help vectors */
	vec3 center;
	vec3 forward;
	vec3 right;
	vec3 up;
} a_Camera;

a_Camera* cameraCreate(
	a_Program* program, vec3 position, float pitch, float yaw
);
void releaseCamera(a_Camera* camera);

void cameraUpdateVectors(a_Camera* camera);
void cameraUpdateMatrices(a_Camera* camera, int* vidmode);
void cameraSendToShader(a_Camera* camera);
/*
 * Update order:
 *		- Handle keyboard and mouse movement events
 * 		- Update vectors
 * 		- Update matrices
 * 		- Send data about projection and view to shader
 * 		- Render scene
*/
void cameraUpdate(a_Camera* camera, int* vidmode);


#endif