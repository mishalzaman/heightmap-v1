#ifndef PLANE_H
#define PLANE_H

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "../structs/meshStruct.h"
#include <vector>

class Plane
{
public:
	Plane(int width, int height);
	~Plane();
	std::vector<MeshStruct> getMesh();
	std::vector<glm::uvec3> getIndices();
private:
	int width;
	int height;
	std::vector<MeshStruct> mesh;
	std::vector<glm::uvec3> indices;

	void generateVerticesAndTextureCoordinates();
	void generateIndices();
	void generateNormals();
};

#endif

