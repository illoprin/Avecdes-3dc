#ifndef A_MESH_H
#define A_MESH_H

#include "../deps.h"
#include "../a_log.h"

typedef struct ModelVertex {
	float vx, vy, vz, tu, tv, nx, ny, nz;
} ModelVertex;

typedef struct Triangle {
	struct ModelVertex vertex[3];
} Triangle;

typedef struct a_Mesh {
	a_Logger* logger;
	const char* name;
	GLuint vbos[3];
	GLuint vao;
	/* Triangles count.
		One Triangle is 3 ModelVerts of 8 4 byte float
	*/
	unsigned count;
	Triangle* triangles;
} a_Mesh;

a_Mesh* meshInit(a_Logger* logger, const char* name, Triangle* triangles, unsigned count);
extern void meshRelease(a_Mesh* mesh);

a_Mesh* loadFromOBJ(const char* assets_path);
extern void initVAO(a_Mesh* mesh);
extern void renderMesh(a_Mesh* mesh);

#endif