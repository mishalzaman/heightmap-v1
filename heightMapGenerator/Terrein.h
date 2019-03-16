#ifndef TERREIN_H
#define TERREIN_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "stb_image.h"

class Shader;

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
	std::vector<glm::vec3> vertices;
	std::vector<glm::uvec3> indices;
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

