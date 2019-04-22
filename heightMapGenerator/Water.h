#ifndef WATER_H
#define WATER_H

#include "structs/meshStruct.h"
#include "primitives/Plane.h"
#include "Shader.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Water
{
public:
	Water(const char* vertexPath, const char* fragmentPath);
	~Water();
	void load(int width, int height);
	void draw();
private:
	int width;
	int height;
	Shader* shader;
	std::vector<MeshStruct> mesh;
	std::vector<glm::uvec3> indices;
	unsigned int VAO;

	void generateBufferData();
};

#endif
