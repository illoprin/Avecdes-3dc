#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <malloc.h>

#define OBJ_FILE_MAX_LINE 256
#define PATH_MAX 256

char* get_full_path(const char* assets_path)
{
	char* fullpath = (char*)malloc(sizeof(char) * PATH_MAX);
	strcpy(fullpath, "assets/");
	strcat(fullpath, assets_path);
	printf("Full path: %s\n", fullpath);
	return fullpath;
}

typedef struct ModelVertex {
	float vx, vy, vz, tu, tv, nx, ny, nz;
} ModelVertex;

typedef struct Triangle {
	struct ModelVertex vertex[3];
} Triangle;


void releaseTriangles(Triangle** triangles, unsigned* count)
{
	if (*triangles != NULL && *count > 0)
	{
		free(*triangles);
		*triangles = NULL;
		*count = 0;
	}
}

void load_from_obj(const char* assets_path, char** model_name, float** vertices,
		float** normals, float** texcoords, unsigned* v_face_count)
{
	// Chesk emptiness of input data
	if ((*model_name) || (*vertices) || (*normals) || (*texcoords))
	{
		fprintf(stderr, "LoadFromOBJ: input pointers must be empty\n");
		return;
	}
	printf("LoadFromOBJ: Start loading from  %s\n", assets_path);

	// Read file
	char* full_path = get_full_path(assets_path);
	FILE* obj_file = fopen(full_path, "r");

	// Current line of file
	char line[OBJ_FILE_MAX_LINE];
	// strtok string
	char* token = NULL;
	// Raw vertices count
	int v_count = 0, vn_count = 0, vt_count = 0;
	// Index of entire output vertex of mesh
	*v_face_count = 0;
	/* --- One vertex size ----------------------- One texcoord size ---------- */
	size_t vertex_size = sizeof(float) * 3; size_t texcoord_size = sizeof(float) * 2;
	float* raw_vertices = NULL; float* raw_normals = NULL; float* raw_texcoords = NULL;
	if (obj_file != NULL)
	{
		// Read file line by line
		while (fgets(line, sizeof(line), obj_file))
		{
			token = strtok(line, " ");
			if (!strncmp(token, "o", 1))
			{
				// Get file name
				char* name = strtok(NULL, " ");
				// Get model name string without \n escape sequence
				unsigned name_len = strlen(name) - 1;

				// Assign model name string to output field
				(*model_name) = (char*)malloc(sizeof(char) * name_len);
				strncpy((*model_name), name, name_len);
				printf("Model name is: %s\n", (*model_name));
			}
			else if (!strcmp(token, "v"))
			{
				// Vertex
				if (v_count == 0)
					raw_vertices = 
						(float*)malloc(vertex_size);
				else
					raw_vertices = 
						(float*)realloc(raw_vertices, (v_count + 1) * vertex_size);
				

				raw_vertices[v_count * 3 + 0] = atof(strtok(NULL, " "));
				raw_vertices[v_count * 3 + 1] = atof(strtok(NULL, " "));
				raw_vertices[v_count * 3 + 2] = atof(strtok(NULL, " "));
				v_count++;
			}
			else if (!strcmp(token, "vn"))
			{
				// Normal
				if (vn_count == 0)
					raw_normals = 
						(float*)malloc(vertex_size);
				else
					raw_normals = 
						(float*)realloc(raw_normals, (vn_count + 1) * vertex_size);
				
				raw_normals[vn_count * 3 + 0] = atof(strtok(NULL, " "));
				raw_normals[vn_count * 3 + 1] = atof(strtok(NULL, " "));
				raw_normals[vn_count * 3 + 2] = atof(strtok(NULL, " "));
				vn_count++;
			}
			else if (!strcmp(token, "vt"))
			{
				// Texcoord
				if (vt_count == 0)
					raw_texcoords = 
						(float*)malloc(texcoord_size);
				else
					raw_texcoords = 
						(float*)realloc(raw_texcoords, (vt_count + 1) * texcoord_size);
				
				raw_texcoords[vt_count * 2 + 0] = atof(strtok(NULL, " "));
				raw_texcoords[vt_count * 2 + 1] = atof(strtok(NULL, " "));
				vt_count++;
			}
			else if (!strcmp(token, "f"))
			{
				unsigned decrement = 1;
				// Read triangle - 3 vertices
				for (unsigned i = 0; i < 3; ++i)
				{
					char* v_index = strtok(NULL, " ");
					int iv, it, in;
					sscanf(v_index, "%d/%d/%d", &iv, &it, &in);
					// Vertex output count - abs vertex count
					unsigned vo_count = *v_face_count;
					
					// Allocate memory for vertices, texcoords and normals
					// One face (triagle) - 3 verts and normals and 2 texcoords
					if (vo_count == 0)
					{
						(*vertices) = (float*)malloc(vertex_size);
						(*normals) = (float*)malloc(vertex_size);
						(*texcoords) = (float*)malloc(texcoord_size);
					}
					else
					{
						(*vertices) = (float*)realloc((*vertices), (vo_count + 1) * vertex_size);	
						(*normals) = (float*)realloc((*normals), (vo_count + 1) * vertex_size);	
						(*texcoords) = (float*)realloc((*texcoords), (vo_count + 1) * texcoord_size);
					}

					// Assign vertices by iv (index_vertices) to input vertices array
					(*vertices)[vo_count * 3 + 0] = raw_vertices[(iv - decrement) * 3 + 0]; // X
					(*vertices)[vo_count * 3 + 1] = raw_vertices[(iv - decrement) * 3 + 1]; // Y
					(*vertices)[vo_count * 3 + 2] = raw_vertices[(iv - decrement) * 3 + 2]; // Z
					// Assign texcoord by it (index_texcoord) to input texcoord array
					(*texcoords)[vo_count * 2 + 0] = raw_texcoords[(it - decrement) * 2 + 0]; // U
					(*texcoords)[vo_count * 2 + 1] = raw_texcoords[(it - decrement) * 2 + 1]; // V
					// Assign normals by it (index_normals) to input normals array
					(*normals)[vo_count * 3 + 0] = raw_normals[(in - decrement) * 3 + 0]; // X
					(*normals)[vo_count * 3 + 1] = raw_normals[(in - decrement) * 3 + 1]; // Y
					(*normals)[vo_count * 3 + 2] = raw_normals[(in - decrement) * 3 + 2]; // Z
					(*v_face_count)++;
				}
			}
		}
		// Release resources
		fclose(obj_file);
		printf("LoadFromOBJ: Model %s loaded successfully\n", full_path);
		printf("LoadFromOBJ: Vertex count is: %u\n", *v_face_count);
		if (full_path) free(full_path);
		if (raw_vertices) free(raw_vertices);
		if (raw_normals) free(raw_normals);
		if (raw_texcoords) free(raw_texcoords);
	}
	else
	{
		fprintf(stderr, "LoadFromOBJ: Unable to open obj file.\n");
		free(full_path);
		fclose(obj_file);
	}
}

// Load triangles from obj
void load_t_from_obj(const char* assets_path, char** model_name,
		Triangle** triangles, unsigned* total_triangles)
{
	// Chesk emptiness of input data
	if ((*model_name) || (*triangles))
	{
		fprintf(stderr, "LoadFromOBJ: input pointers must be empty\n");
		return;
	}
	printf("LoadFromOBJ: Start loading from  %s\n", assets_path);

	// Read file
	char* full_path = get_full_path(assets_path);
	FILE* obj_file = fopen(full_path, "r");

	// Current line of file
	char line[OBJ_FILE_MAX_LINE];
	// strtok string
	char* token = NULL;
	// Raw vertices count
	int v_count = 0, vn_count = 0, vt_count = 0;
	// Index of entire output vertex of mesh
	*total_triangles = 0;
	// Index number decrement
	unsigned decrement = 1;
	/* --- One vertex size ----------------------- One texcoord size ---------- */
	size_t vertex_size = sizeof(float) * 3; size_t texcoord_size = sizeof(float) * 2;
	float* raw_vertices = NULL; float* raw_normals = NULL; float* raw_texcoords = NULL;
	if (obj_file != NULL)
	{
		// Read file line by line
		while (fgets(line, sizeof(line), obj_file))
		{
			token = strtok(line, " ");
			if (!strncmp(token, "o", 1))
			{
				// Get file name
				char* name = strtok(NULL, " ");
				// Get model name string without \n escape sequence
				unsigned name_len = strlen(name) - 1;

				// Assign model name string to output field
				(*model_name) = (char*)malloc(sizeof(char) * name_len);
				strncpy((*model_name), name, name_len);
				printf("Model name is: %s\n", (*model_name));
			}
			else if (!strcmp(token, "v"))
			{
				// Vertex
				if (v_count == 0)
					raw_vertices = 
						(float*)malloc(vertex_size);
				else
					raw_vertices = 
						(float*)realloc(raw_vertices, (v_count + 1) * vertex_size);
				

				raw_vertices[v_count * 3 + 0] = atof(strtok(NULL, " "));
				raw_vertices[v_count * 3 + 1] = atof(strtok(NULL, " "));
				raw_vertices[v_count * 3 + 2] = atof(strtok(NULL, " "));
				v_count++;
			}
			else if (!strcmp(token, "vn"))
			{
				// Normal
				if (vn_count == 0)
					raw_normals = 
						(float*)malloc(vertex_size);
				else
					raw_normals = 
						(float*)realloc(raw_normals, (vn_count + 1) * vertex_size);
				
				raw_normals[vn_count * 3 + 0] = atof(strtok(NULL, " "));
				raw_normals[vn_count * 3 + 1] = atof(strtok(NULL, " "));
				raw_normals[vn_count * 3 + 2] = atof(strtok(NULL, " "));
				vn_count++;
			}
			else if (!strcmp(token, "vt"))
			{
				// Texcoord
				if (vt_count == 0)
					raw_texcoords = 
						(float*)malloc(texcoord_size);
				else
					raw_texcoords = 
						(float*)realloc(raw_texcoords, (vt_count + 1) * texcoord_size);
				
				raw_texcoords[vt_count * 2 + 0] = atof(strtok(NULL, " "));
				raw_texcoords[vt_count * 2 + 1] = atof(strtok(NULL, " "));
				vt_count++;
			}
			else if (!strcmp(token, "f"))
			{
				if (*total_triangles == 0)
				{
					(*triangles) = (Triangle*)malloc(sizeof(Triangle));
				}
				else
				{
					(*triangles) = (Triangle*)realloc((*triangles), sizeof(Triangle) * (*total_triangles + 1));	 
				}
				// Clear new triangle triangle
				memset(&((*triangles)[*total_triangles]), 0, sizeof(Triangle));

				// Read triangle - 3 vertices, assign data to entire modelvertex
				for (unsigned i = 0; i < 3; ++i)
				{
					ModelVertex* vertex = &((*triangles)[*total_triangles].vertex[i]);
					char* v_index = strtok(NULL, " ");
					int iv, it, in;
					sscanf(v_index, "%d/%d/%d", &iv, &it, &in);

					// Assign vertices normals and texcoords to single triangle
					// Vertex
					vertex->vx = raw_vertices[(iv - decrement) * 3 + 0];
					vertex->vy = raw_vertices[(iv - decrement) * 3 + 1];
					vertex->vz = raw_vertices[(iv - decrement) * 3 + 2];

					// Texcoord
					vertex->tu = raw_texcoords[(it - decrement) * 2 + 0];
					vertex->tv = raw_texcoords[(it - decrement) * 2 + 1];

					// Normal
					vertex->nx = raw_normals[(in - decrement) * 3 + 0];
					vertex->ny = raw_normals[(in - decrement) * 3 + 1];
					vertex->nz = raw_normals[(in - decrement) * 3 + 2];
					
				}
				(*total_triangles)++;
			}
		}
		// Release resources
		fclose(obj_file);
		printf("LoadFromOBJ: Model %s loaded successfully\n", full_path);
		printf("LoadFromOBJ: Count of triangles is: %u\n", *total_triangles);
		if (full_path) free(full_path);
		if (raw_vertices) free(raw_vertices);
		if (raw_normals) free(raw_normals);
		if (raw_texcoords) free(raw_texcoords);
	}
	else
	{
		fprintf(stderr, "LoadFromOBJ: Unable to open obj file.\n");
		free(full_path);
		fclose(obj_file);
	}
}

float* pack_triangles(Triangle** triangles, unsigned* f_count)
{
	if ((*triangles) == NULL || *f_count <= 0)
		fprintf(stderr, "PackTriangles: Triangles* is nullptr or count of triangles is 0 or less\n");
	float* data = (float*)malloc(24 * (*f_count) * sizeof(float));
	if (data == NULL)
	{
		fprintf(stderr, "PackTriangles: Unable to allocate memory\n");
		return NULL;
	}

	for (unsigned i = 0; i < *f_count; ++i)
	{
		Triangle* tri = triangles[i];
		memcpy(data + (i * 24), tri->vertex, sizeof(ModelVertex) * 3);
	}
	return data;
}

int main()
{
	char* model_name = NULL; unsigned f_count = 0;
	Triangle* triangles;
	printf("Size of Triangle struct: %lu\n", sizeof(Triangle));
	load_t_from_obj("obj/tree_foliage.obj", &model_name, &triangles, &f_count);
	
	/*
		for (unsigned i = 0; i < f_count; i++)
		{

			Triangle* tri = &(triangles[i]);
			for (unsigned j = 0; j < 3; j++)
			{
				ModelVertex* vert = &(tri->vertex[j]);
				printf("%d: vx: %.2f vy: %.2f vz: %.2f tu: %.2f tv: %.2f nx: %.2f ny: %.2f nz: %.2f\n", i,
					vert->vx, vert->vy, vert->vz, vert->tu, vert->tv, vert->nx, vert->ny, vert->nz);
			}
			printf("\n");
		}

	*/
	
	
	float* packed_data = pack_triangles(&triangles, &f_count);
	printf("Size of packed data: %lu\n", sizeof(packed_data));

	// Release resources
	releaseTriangles(&triangles, &f_count);
	if (model_name) free(model_name);
	if (packed_data) free(packed_data);

	return 0;
}