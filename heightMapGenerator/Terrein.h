#ifndef TERREIN_H
#define TERREIN_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Shader;

class Terrein
{
public:
	Terrein(unsigned int width, unsigned height);
	~Terrein();
	void build();
	void render();
private:
	unsigned int mapWidth;
	unsigned int mapHeight;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	Shader* shader;
};

#endif

