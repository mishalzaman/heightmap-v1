#ifndef TERREIN_H
#define TERREIN_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include "stb_image.h"
#include "CameraFP.h"

class Shader;

struct MeshV3 {
	glm::vec3 position;
	glm::vec3 normal = glm::vec3(0,0,0);
	glm::vec2 texture;
};

class Terrein
{
public:
	Terrein();
	~Terrein();
	void load();
	void draw(CameraFP &camera, glm::vec3 lampPosition);
	void cleanup();
	void setScale(float scale);
	int getWidth();
	int getHeight();
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
	float scale = -0.2;
	Shader* shader;
	void build();
	void getHeightMapImageData();

	unsigned int texture;
	unsigned char* diffuseData;
	void getDIffuseMap();

};

#endif

