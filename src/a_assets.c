#ifndef A_ASSETS_C
#define A_ASSETS_C

#include "a_assets.h"

/*
	LEFT: +x
	RIGHT: -x
*/

struct Triangle quad_tris[] = 
{
	{{
		{0.5f, 0.5f, 0.f, 1.f, 1.f, 0.f, 0.f, -1.f},
		{0.5f, -0.5f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f},
		{-0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f}
	}},
	{{
		{-0.5f, -0.5f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f},
		{-0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f},
		{0.5f, 0.5f, 0.f, 1.f, 1.f, 0.f, 0.f, -1.f}
	}}
};

struct Triangle cube_tris[] = 
{
	/* Front */
	{{
		{0.5f, 0.5f, -.5f, 1.f, 1.f, 0.f, 0.f, -1.f},
		{0.5f, -0.5f, -.5f, 1.f, 0.f, 0.f, 0.f, -1.f},
		{-0.5f, -0.5f, -.5f, 0.f, 0.f, 0.f, 0.f, -1.f}
	}},
	{{
		{-0.5f, -0.5f, -.5f, 0.f, 0.f, 0.f, 0.f, -1.f},
		{-0.5f, 0.5f, -.5f, 0.f, 1.f, 0.f, 0.f, -1.f},
		{0.5f, 0.5f, -.5f, 1.f, 1.f, 0.f, 0.f, -1.f}
	}},

	/* Back */
	{{
		{-0.5f, 0.5f, 0.5f, 1.f, 1.f, 0.f, 0.f, 1.f},
		{-0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 0.f, 1.f},
		{0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 1.f}
	}},
	{{
		{0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f, 0.f, 1.f},
		{0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f},
		{-0.5f, 0.5f, 0.5f, 1.f, 1.f, 0.f, 0.f, 1.f}
	}},

	/* Left */
	{{
		{0.5f, -0.5f, -.5f, 1.f, 1.f, 1.f, 0.f, 0.f},
		{0.5f, 0.5f, -.5f, 1.f, 0.f, 1.f, 0.f, 0.f},
		{0.5f, 0.5f, .5f, 0.f, 0.f, 1.f, 0.f, -0.f}
	}},
	{{
		{0.5f, 0.5f, .5f, 0.f, 0.f, 1.f, 0.f, 0.f},
		{0.5f, -0.5f, .5f, 0.f, 1.f, 1.f, 0.f, 0.f},
		{0.5f, -0.5f, -.5f, 1.f, 1.f, 1.f, 0.f, 0.f}
	}},

	/* Right */
	{{
		{-0.5f, -0.5f, -0.5f, 1.f, 1.f, -1.f, 0.f, 0.f},
		{-0.5f, -0.5f, 0.5f, 1.f, 0.f, -1.f, 0.f, 0.f},
		{-0.5f, 0.5f, 0.5f, 0.f, 0.f, -1.f, 0.f, 0.f}
	}},
	{{
		{-0.5f, 0.5f, 0.5f, 0.f, 0.f, -1.f, 0.f, 0.f},
		{-0.5f, 0.5f, -0.5f, 0.f, 1.f, -1.f, 0.f, 0.f},
		{-0.5f, -0.5f, -0.5f, 1.f, 1.f, -1.f, 0.f, 0.f}
	}},

	/* Top */
	{{
		{-0.5f, 0.5f, 0.5f, 1.f, 1.f, 0.f, 1.f, 0.f},
		{0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f, 0.f},
		{0.5f, 0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 0.f}
	}},
	{{
		{0.5f, 0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 0.f},
		{-0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f, 0.f},
		{-0.5f, 0.5f, 0.5f, 1.f, 1.f, 0.f, 1.f, 0.f}
	}},

	/* Bottom */
	{{
		{-0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, -1.f, 0.f},
		{0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, -1.f, 0.f},
		{0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f, -1.f, 0.f}
	}},
	{{
		{0.5f, -0.5f, 0.5f, 0.f, 0.f, 0.f, -1.f, 0.f},
		{-0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, -1.f, 0.f},
		{-0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, -1.f, 0.f}
	}}
};

a_Mesh* AssetsGetQuadMesh(a_Logger* log, vec3 size)
{
	a_Mesh* mesh = meshInit(log, "Quad");
	// Init VAO of quad mesh
	meshAddTriangles(mesh, quad_tris, 2);
	return mesh;
};

a_Mesh* AssetsGetCubeMesh(a_Logger* log, vec3 size)
{
	a_Mesh* mesh = meshInit(log, "Cube");
	// Init VAO of cube mesh
	meshAddTriangles(mesh, cube_tris, 12);
	return mesh;
};

#endif