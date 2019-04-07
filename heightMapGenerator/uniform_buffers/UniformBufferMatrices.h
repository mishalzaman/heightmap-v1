#ifndef UNIFORM_BUFFER_MATRICES_H
#define UNIFORM_BUFFER_MATRICES_H

#include "../Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

/*	uniform Matrices
		mat4 projection;
		mat4 view;
*/

class UniformBufferMatrices
{
public:
	UniformBufferMatrices();
	~UniformBufferMatrices();
	void updateUBOMatricesProjection(glm::mat4 projection);
	void updateUBOMatricesView(glm::mat4 view);
private:
	unsigned int UBOMatrices;
	void setUBOMatrices();
};

#endif