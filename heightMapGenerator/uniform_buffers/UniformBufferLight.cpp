#include "UniformBufferLight.h"

UniformBufferLight::UniformBufferLight()
{
	this->setUBO();
}

UniformBufferLight::~UniformBufferLight()
{
}

void UniformBufferLight::updatePosition(glm::vec4 position)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(position));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferLight::updateColour(glm::vec4 colour)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(colour));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferLight::setUBO()
{
	glGenBuffers(1, &this->UBO);
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBO);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, 1, this->UBO);
}
