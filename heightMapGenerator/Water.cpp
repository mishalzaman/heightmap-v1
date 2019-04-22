#include "Water.h"

Water::Water(const char* vertexPath, const char* fragmentPath)
{
	this->shader = new Shader(vertexPath, fragmentPath);
}

Water::~Water()
{
	delete this->shader;
}

void Water::load(int width, int height)
{
	Plane* plane = new Plane(width, height);
	 
	this->mesh = plane->getMesh();
	this->indices = plane->getIndices();

	delete plane;

	this->generateBufferData();
}

void Water::draw()
{
	float scale = 32.0;

	this->shader->use();
	glBindVertexArray(this->VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, 2.0, 0.0));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	this->shader->setMat4("model", model);

	glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size() * 3, GL_UNSIGNED_INT, 0);
}

void Water::generateBufferData()
{
	unsigned int VBO;
	unsigned int IBO;

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, this->mesh.size() * sizeof(MeshStruct), &this->mesh[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(glm::uvec3), glm::value_ptr(this->indices[0]), GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshStruct), (void*)0);
	glEnableVertexAttribArray(0);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshStruct), (void*)offsetof(MeshStruct, normal));
	glEnableVertexAttribArray(1);

	// textures
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshStruct), (void*)offsetof(MeshStruct, texture));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}
