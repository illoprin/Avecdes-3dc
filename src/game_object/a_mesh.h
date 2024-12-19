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

typedef struct uint_list {
	GLuint* data;
	char size;
} uint_list;

typedef struct a_Mesh {
	a_Logger* logger;
	const char* name;
	uint_list vbos_list;
	uint_list attribs_list;
	GLuint vao;
	/* Triangles count.
		One Triangle is 3 ModelVerts of 8 4 byte float
	*/
	unsigned count;
	Triangle* tris;
} a_Mesh;

a_Mesh* meshInit(a_Logger* logger, const char* name);

a_Mesh* loadFromOBJ(const char* assets_path);
extern void addFloatBuffer(float* data, unsigned size, unsigned stride);
extern void addIndexBuffer(int* data, unsigned* size);

extern void meshAddTriangles(a_Mesh* mesh, Triangle* tris, unsigned count);

extern void meshRender(a_Mesh* mesh);

extern void meshReleaseAll(a_Mesh* mesh);
extern void meshReleaseVAO(a_Mesh* mesh);

Triangle* meshGetTriangles(a_Mesh* mesh);

#endif