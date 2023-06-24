////=-= =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-=       =-= =-= =-= =-= =-= =-= =-= 

#pragma once

#include <map>

#include "Meshes.h"
#include "Physics.h"
#include "BlockTextureAtlas.h"


class World
{
private:
	std::vector<Mesh> chunkMeshes; //(The chunk's mesh which is what's rendered; can be updated using certain functions.)
	Physics* phys;


public:
	World(Physics* p) {
		phys = p;
	}

	void Draw(); //(Used to initiate rendering the chunk's mesh, which is actually stored in "chunkMesh" and can be updated by certain functions.)

	void makeTheWorld();

	void cleanup(); //(Used for cleaning up the mesh, more specifically it has to do with VBO VAO EBO stuff.)
};
