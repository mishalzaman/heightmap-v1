#ifndef MESH_STRUCT_H
#define MESH_STRUCT_H

#include <glm/glm.hpp>

struct MeshStruct {
	glm::vec3 position;
	glm::vec3 normal = glm::vec3(0, 0, 0);
	glm::vec2 texture;
};

#endif