#ifndef UNIFORM_BUFFER_LIGHT_H
#define UNIFORM_BUFFER_LIGHT_H

/*	uniform Light
		vec4 position;
		vec4 colour;
*/

#include "../Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class UniformBufferLight
{
public:
	UniformBufferLight();
	~UniformBufferLight();
	void updatePosition(glm::vec4 position);
	void updateColour(glm::vec4 colour);
private:
	unsigned int UBO;
	void setUBO();
};

#endif UNIFORM_BUFFER_LIGHT_H