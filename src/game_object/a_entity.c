#ifndef A_ENTITY_C
#define A_ENTITY_C

#include "a_entity.h"

static void initModel(a_Entity* entity)
{
	glm_mat4_copy(GLM_MAT4_IDENTITY, entity->model);
	/* Init pointers to first elements of transforms */
	float* rot = entity->rotation;
	float* pos = entity->position;
	float* scl = entity->scale;
	glm_scale(entity->model, scl);
	vec3 axisX = {1.f, 0.f, 0.f};
	glm_rotate(entity->model, glm_rad(rot[0]), axisX);
	vec3 axisY = {0.f, 1.f, 0.f};
	glm_rotate(entity->model, glm_rad(rot[1]), axisY);
	vec3 axisZ = {0.f, 0.f, 1.f};
	glm_rotate(entity->model, glm_rad(rot[2]), axisZ);
	glm_translate(entity->model, pos);
	/* TODO: multiply entity model to parent model if has parent */
}
a_Entity* entityCreate(a_Mesh* mesh, a_Program* prog, bool is_static, ...)
{
	a_Entity* entity = (a_Entity*)malloc(sizeof(a_Entity));
	entity->mesh = mesh;
	entity->program = prog;
	entity->isStatic = is_static;

	/* Set zero values to origin position scale and rotation*/
	glm_mat4_copy(GLM_MAT4_IDENTITY, entity->origin);
	memset(&entity->position[0], 0, sizeof(vec3));
	memset(&entity->rotation[0], 0, sizeof(vec3));
	glm_vec3_copy((vec3){1.f, 1.f, 1.f}, entity->scale);

	if (is_static)
	{
		va_list transform;
		va_start(transform, is_static);
		
		/* Set entity transforms from args */
		float* position = va_arg(transform, float*);
		float* scale = va_arg(transform, float*);
		float* rotation = va_arg(transform, float*);
		if (position != NULL) glm_vec3_copy(&(position[0]), entity->position);
		if (scale != NULL) glm_vec3_copy(&(scale[0]), entity->scale);
		if (rotation != NULL) glm_vec3_copy(&(rotation[0]), entity->rotation);

		va_end(transform);
		initModel(entity);
	};
	return entity;
}
extern void entityRender(a_Entity* entity)
{
	if (entity != NULL)
	{
		if (!entity->isStatic)
		{
			initModel(entity);
		};
		programSetMatrix4Uniform(entity->program,
			entity->model, "u_model");
		/* TODO: Attach texture & send sampler id */
		meshRender(entity->mesh);
	}
}
/* Parent */
extern void entitySetParent(a_Entity* target, a_Entity* parent)
{
	if (parent != NULL)
	{
		target->parent = (void*)parent;
		target->isStatic = false;
	}
}
/* Setters */
extern void entitySetPosition(a_Entity* entity, float* position)
{
	glm_vec3_copy(position, entity->position);
}
extern void entitySetScale(a_Entity* entity, float* scale)
{
	glm_vec3_copy(scale, entity->scale);
}
extern void entitySetRotation(a_Entity* entity, float* rotation)
{
	glm_vec3_copy(rotation, entity->rotation);
}

/* Changes */
extern void entityMove(a_Entity* entity, float* delta)
{
	glm_vec3_add(entity->position, delta, entity->position);
}
extern void entityResize(a_Entity* entity, float* delta)
{
	glm_vec3_add(entity->scale, delta, entity->scale);
}
extern void entityRotate(a_Entity* entity, float* delta)
{
	glm_vec3_add(entity->rotation, delta, entity->rotation);
}

/* Release */
extern void entityRelease(a_Entity* entity)
{
	if (entity != NULL)
	{
		free(entity);
	};
}
/* Release entity with linked mesh */
extern void entityReleaseAll(a_Entity* entity)
{
	if (entity != NULL)
	{
		meshReleaseAll(entity->mesh);
		free(entity);
	}
}


#endif