#ifndef TERREIN_H
#define TERREIN_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "stb_image.h"

class Shader;

struct MeshV3 {
	glm::vec3 position;
	glm::vec3 normal;
};

class Terrein
{
public:
	Terrein();
	~Terrein();
	void load(unsigned int mapSize);
	void render();
	void cleanup();
private:
	unsigned int mapSize;
	std::vector<glm::uvec3> indices;
	std::vector<MeshV3> mesh;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int IBO;
	unsigned int heightMap;
	unsigned char *imageData;
	int imageWidth;
	int imageHeight;
	Shader* shader;
	void build();
	void getHeightMapImageData();
};

#endif

