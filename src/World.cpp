#include "World.h"

void World::makeTheWorld()
{
	std::vector<float> h;
	for (int i = 0; i < 64; i++) {
		h.push_back(sqrt(i));
	}
	phys->MakeHeightField(h,8);

	std::vector<Vertex> v;
	std::vector<GLuint> ind;
	for (int i = 0; i < 64; i++)
		v.push_back({ glm::vec3(floor(i / 8),h[i],i % 8),glm::vec2(0),glm::vec3((float)(i)/16) });

	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			ind.push_back(i + (8 * j));
			ind.push_back(i+1 + (8 * j));
			ind.push_back(i + (8 * (j+1)));

			ind.push_back(i + 1 + (8 * j));
			ind.push_back(i + 1 + (8 * (j + 1)));
			ind.push_back(i + (8 * (j + 1)));
			
		}
	}
	
	chunkMeshes.push_back(Mesh(v, ind));
}

void World::Draw() {
	chunkMeshes[0].draw();
}


