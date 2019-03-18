#ifndef LAMP_H
#define LAMP_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader;

class Lamp
{
public:
	Lamp();
	~Lamp();
	void load();
	void update();
	void render();
	void cleanup();
private:
	glm::vec3 position;
	unsigned int VAO;
	Shader* shader;
};

#endif

