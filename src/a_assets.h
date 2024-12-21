#ifndef A_ASSETS_H
#define A_ASSETS_H

#include "defs.h"
#include "game_object/a_entity.h"
#include "game_object/a_mesh.h"


/* TODO: Cube mesh triangles */

a_Mesh* AssetsGetQuadMesh(a_Logger* log, vec3 size);
a_Mesh* AssetsGetCubeMesh(a_Logger* log, vec3 size);


#endif