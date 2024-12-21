#ifndef A_ENTITY_H
#define A_ENTITY_H

#include "a_mesh.h"
#include "../a_program.h"
#include "../deps.h"

typedef struct a_Entity {
	bool isStatic;
	a_Mesh* mesh;
	a_Program* program;
	void* parent; /* Pointer to another entity object */
	mat4 model;
	mat4 origin;
	vec3 position;
	vec3 rotation;
	vec3 scale;
} a_Entity;

a_Entity* entityCreate(a_Mesh* mesh, a_Program* prog, bool is_static, ...);
extern void entityRelease(a_Entity* entity);
extern void entityRender(a_Entity* entity);
/* Parent */
extern void entitySetParent(a_Entity* target, a_Entity* parent);
/* Setters */
extern void entitySetPosition(a_Entity* entity, float* position);
extern void entitySetScale(a_Entity* entity, float* scale);
extern void entitySetRotation(a_Entity* entity, float* rotation);
/* Changes */
extern void entityMove(a_Entity* entity, float* delta);
extern void entityResize(a_Entity* entity, float* delta);
extern void entityRotate(a_Entity* entity, float* delta);
/* Release */
extern void entityRelease(a_Entity* entity);
/* Release entity with linked mesh */
extern void entityReleaseAll(a_Entity* entity);

#endif