#ifndef A_DEFS_H
#define A_DEFS_H

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define WIN_RESIZEABLE 0
#define WIN_TITLE "Game"
#define WIN_MAX_TITLE 64 /* Max 64 symbols in title */
#define MAX_FPS 120

#define LOG_PATH "tmp"
#define LOG_MAX 1024 /* Max lines in log */
#define PATH_CHAR_MAX 128
#define MAX_LINE 256 /* Max char in line in read/write stream */

/* Camera */
#define CAMERA_FOV_V 85.f
#define CAMERA_NEAR .01f
#define CAMERA_FAR 500.f

/* Player */
#define PLAYER_SENSITIVITY 12.f
#define PLAYER_SPEED 5.f

/* 	Enum design:
 *		PL - name of entity
 *		M - type of action (movent current ex)
 *		FORWARD - direction
 */
enum PlayerActionList {
	PL_M_FORWARD = 0,
	PL_M_BACKWARD,
	PL_M_LEFT,
	PL_M_RIGHT,
	PL_W_FOCUS,		
};

/* Directions */
#define DIR_UP  (vec3){0.f, 1.f, 0.f}
#define DIR_RIGHT (vec3){1.f, 0.f, 0.f}
#define DIR_FORWARD (vec3){0.f, 0.f, 1.f}

/* Parametres */
#define PHYS_GRAVITY (vec3){0, -9.81f, 0.f}



#endif