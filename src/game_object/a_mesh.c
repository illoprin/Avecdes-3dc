#ifndef A_MESH_C
#define A_MESH_C

#include "a_mesh.h"

a_Mesh* meshInit(a_Logger* logger, const char* name)
{
	// float* vertices is local extern variable
	a_Mesh* mesh = (a_Mesh*)malloc(sizeof(a_Mesh));
	mesh->logger = logger;
	mesh->name = name;

	// Gen VAO
	glGenVertexArrays(1, &mesh->vao);

	return mesh;
};

static void meshVAOBind(a_Mesh* mesh)
{
	// Bind created VAO object
	glBindVertexArray(mesh->vao);
};

static void meshGenBuffer(a_Mesh* mesh, void* data, size_t comp_size)
{
	meshVAOBind(mesh);
	if (data == NULL)
	{
		lLog(mesh->logger, "[WARNING] Mesh.%s - Unable to generate VBO object. Data is nullptr\n", mesh->name);
		return;
	}
	unsigned* size = (unsigned*)&mesh->vbos_list.size;
	if (*size == 0)
	{
		mesh->vbos_list.data = (GLuint*)malloc(sizeof(GLuint));
		(*size)++;
	}
	else 
	{
		mesh->vbos_list.data = (GLuint*)realloc(mesh->vbos_list.data, sizeof(GLuint) * (*size + 1));
		(*size)++;
	}
	glGenBuffers(1, &mesh->vbos_list.data[*size - 1]);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos_list.data[*size - 1]);
	glBufferData(GL_ARRAY_BUFFER, comp_size, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	lLog(mesh->logger, "[INFO] Mesh.%s - Generated new VBO object with index %u\n",
			mesh->name, mesh->vbos_list.data[*size - 1]);
};

static void meshAddAttribute(a_Mesh* mesh, GLuint buffer, unsigned comps, size_t stride, int offset)
{
	meshVAOBind(mesh);
	unsigned* size = (unsigned*)&mesh->attribs_list.size;
	if (*size == 0)
	{
		mesh->attribs_list.data = (GLuint*)malloc(sizeof(GLuint));
		(*size)++;
	}
	else 
	{
		mesh->attribs_list.data = (GLuint*)realloc(mesh->attribs_list.data, sizeof(GLuint) * (*size + 1));
		(*size)++;
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	mesh->attribs_list.data[*size - 1] = *size - 1;
	glEnableVertexAttribArray((GLuint)(*size - 1));
	glVertexAttribPointer((GLuint)(*size - 1), comps, GL_FLOAT, GL_FALSE, stride, (void*)offset);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	lLog(mesh->logger, "[INFO] Mesh.%s - Created new attribute pointer with index %u\n",
			mesh->name, mesh->attribs_list.data[*size - 1]);
};

static void meshEnableAttributes(a_Mesh* mesh)
{
	uint_list* al = &mesh->attribs_list;
	for (unsigned i = 0; i < al->size; i++)
		glEnableVertexAttribArray(al->data[i]);
};

static void meshDisableAttributes(a_Mesh* mesh)
{
	uint_list* al = &mesh->attribs_list;
	for (unsigned i = 0; i < al->size; i++)
		glDisableVertexAttribArray(al->data[i]);
};

static void meshDeleteVBOs(a_Mesh* mesh)
{
	uint_list* vl = &mesh->vbos_list;
	for (unsigned i = 0; i < vl->size; i++)
		glDeleteBuffers(1, (&vl->data[i]));
}

extern void meshAddTriangles(a_Mesh* mesh, Triangle* triangles, unsigned count)
{
	if (triangles == NULL || count < 1)
	{
		lLog(mesh->logger, "[WARNING] Mesh.%s - Unable to create VAO, triangles count is less then one.\n", mesh->name);
		return;
	}

	mesh->tris = triangles;
	mesh->count = count * 3;

	meshGenBuffer(mesh, &(triangles[0].vertex[0]),
			(count * sizeof(ModelVertex) * 3));
	meshAddAttribute(mesh, mesh->vbos_list.data[0], 3,
			sizeof(ModelVertex), offsetof(ModelVertex, vx));
	meshAddAttribute(mesh, mesh->vbos_list.data[0], 2,
			sizeof(ModelVertex), offsetof(ModelVertex, tu));
	meshAddAttribute(mesh, mesh->vbos_list.data[0], 3,
			sizeof(ModelVertex), offsetof(ModelVertex, nx));
	
	// Unbind VAO
	glBindVertexArray(0);
}

extern void meshRender(a_Mesh* mesh)
{
	meshVAOBind(mesh);
	meshEnableAttributes(mesh);
	glDrawArrays(GL_TRIANGLES, 0, mesh->count);
	meshDisableAttributes(mesh);
	glBindVertexArray(0);
};

extern void meshReleaseVAO(a_Mesh* mesh)
{
	if (mesh)
	{
		// Release VBO and indices list
		if (mesh->vbos_list.data)
		{
			meshDeleteVBOs(mesh);
			free(mesh->vbos_list.data);
		}

		// Release attribute list
		if (mesh->attribs_list.data) free(mesh->attribs_list.data);

		// Release VAO
		glDeleteVertexArrays(1, &mesh->vao);
		lLog(mesh->logger, "[INFO] Mesh.%s - VAO and VBO cleared. Prepared for reuse\n", mesh->name);
	}
}

extern void meshReleaseAll(a_Mesh* mesh)
{
	if (mesh) {
		// Release VBO and indices list
		if (mesh->vbos_list.data)
		{
			meshDeleteVBOs(mesh);
			free(mesh->vbos_list.data);
		}

		// Release attribute list
		if (mesh->attribs_list.data) free(mesh->attribs_list.data);
		
		// Release VAO
		glDeleteVertexArrays(1, &mesh->vao);
			
		lLog(mesh->logger, "[INFO] Mesh.%s - Released!\n", mesh->name);
		free(mesh);
	}
};

#endif