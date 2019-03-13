#include "UniformBufferMatrices.h"

using namespace std;

UniformBufferMatrices::UniformBufferMatrices()
{
	this->setUBOMatrices();
}

UniformBufferMatrices::~UniformBufferMatrices()
{
}

void UniformBufferMatrices::setUBOMatrices()
{
	glGenBuffers(1, &this->UBOMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	// define the range of the buffer that links to a uniform binding point
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, this->UBOMatrices);
}

void UniformBufferMatrices::updateUBOMatricesProjection(glm::mat4 projection)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void UniformBufferMatrices::updateUBOMatricesView(glm::mat4 view)
{
	glBindBuffer(GL_UNIFORM_BUFFER, this->UBOMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}