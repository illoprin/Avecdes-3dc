#ifndef A_MESH_C
#define A_MESH_C

#include "a_mesh.h"

a_Mesh* meshInit(a_Logger* logger, const char* name,
		Triangle* triangles, unsigned count)
{
	// float* vertices is local extern variable
	a_Mesh* mesh = (a_Mesh*)malloc(sizeof(a_Mesh));
	mesh->logger = logger;
	mesh->triangles = triangles;
	mesh->count = count;
	mesh->name = name;
	return mesh;
};

extern void initVAO(a_Mesh* mesh)
{
	// Gen VAO
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	// Gen one VBO
	glGenBuffers(1, &mesh->vbos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[0]);

	// Compute strides
	int comp_count = mesh->count * (sizeof(ModelVertex) * 3); // All components (float 4 byte) count

	// Send data to buffer
	glBufferData(GL_ARRAY_BUFFER, comp_count, &(mesh->triangles[0].vertex[0]), GL_STATIC_DRAW);

	lLog(mesh->logger, "[INFO] Mesh.%s - VBO initialized\n", mesh->name);
	
	glEnableVertexAttribArray(0);
	// Attribute: Vertex
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, vx));

	glEnableVertexAttribArray(1);
	// Attribute: Texcoord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, tu));

	glEnableVertexAttribArray(2);
	// Attribute: Normal
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(ModelVertex), (void*)offsetof(ModelVertex, nx));

	lLog(mesh->logger, "[INFO] Mesh.%s - VAO initialized\n", mesh->name);

	// Unbind VAO
	glBindVertexArray(0);
}

extern void renderMesh(a_Mesh* mesh)
{
	glBindVertexArray(mesh->vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh->count);
	glBindVertexArray(0);
};

extern void meshRelease(a_Mesh* mesh)
{
	if (mesh) {
		// Release VAO and VBO
		if (mesh->vbos)
			glDeleteBuffers(1, &mesh->vbos[0]);
		glDeleteVertexArrays(1, &mesh->vao);
		lLog(mesh->logger, "[INFO] Mesh.%s - VBO and VAO released!\n", mesh->name);
		free(mesh);
	}
};


#endif