#include "Light.h"
#include "Shader.h"

Light::Light(glm::vec3 position)
{
	this->shader = new Shader("shaders/lamp.vert", "shaders/lamp.frag");
	this->shader->setUBOMatrices();
	this->position = position;
}

Light::~Light()
{
	this->cleanup();
}

void Light::load()
{
	float vertices[] = {
	 0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	unsigned int VBO, EBO;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Light::update()
{
}

void Light::draw()
{
	this->shader->use();
	glBindVertexArray(this->VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, this->position);
	this->shader->setMat4("model", model);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

glm::vec3 Light::getPosition()
{
	return this->position;
}

void Light::updatePosition(glm::vec3 position)
{
	this->position = position;
}

void Light::cleanup()
{
	if (this->VAO) {
		glDeleteVertexArrays(1, &this->VAO);
	}

	delete(this->shader);
}
