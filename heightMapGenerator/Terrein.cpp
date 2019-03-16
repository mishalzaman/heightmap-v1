#include "Terrein.h"
#include "Shader.h"

using namespace std;

Terrein::Terrein()
{
	this->shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
	this->shader->setUBOMatrices();
}

Terrein::~Terrein()
{
	this->cleanup();
}

void Terrein::load(unsigned int mapSize)
{
	this->mapSize = mapSize;

	this->getHeightMapImageData();
	this->build();
	stbi_image_free(this->imageData);
}

void Terrein::build()
{
	// https://stackoverflow.com/questions/47086858/create-a-grid-in-opengl
	for (int i = 0; i <= this->mapSize; ++i)
	{
		for (int j = 0; j <= this->mapSize; ++j)
		{
			float x = (float)j / (float)this->mapSize;
			float y = (float)i / (float)this->mapSize;

			// float pixel = this->imageData[this->imageWidth * (j*this->imageWidth/this->mapSize) + (i*this->imageWidth/this->mapSize)];
			float pixel = this->imageData[this->imageWidth * j + i];

			float z = float(pixel/256.0);
			this->vertices.push_back(glm::vec3(x, y, z));
		}
	}

	for (int j = 0; j < this->mapSize; ++j)
	{
		for (int i = 0; i < this->mapSize; ++i)
		{
			int row1 = j * (this->mapSize + 1);
			int row2 = (j + 1) * (this->mapSize + 1);

			// triangle 1
			this->indices.push_back(glm::uvec3(row1 + i, row1 + i + 1, row2 + i + 1));

			// triangle 2
			this->indices.push_back(glm::uvec3(row1 + i, row2 + i + 1, row2 + i));
		}
	}

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->IBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(glm::vec3), glm::value_ptr(this->vertices[0]), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(glm::uvec3), glm::value_ptr(this->indices[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void Terrein::getHeightMapImageData()
{
	std::string path = "assets/heightmap.png";
	this->imageData = stbi_load(path.c_str(), &this->imageWidth, &this->imageHeight, NULL, 1);
}

void Terrein::render()
{
	this->shader->use();
	glBindVertexArray(this->VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
	model = glm::scale(model, glm::vec3(8.0, 8.0, 8.0));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	this->shader->setMat4("model", model);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size() * 3, GL_UNSIGNED_INT, 0);
}

void Terrein::cleanup()
{
	if (this->VBO) {
		glDeleteBuffers(1, &this->VBO);
	}

	if (this->IBO) {
		glDeleteBuffers(1, &this->IBO);
	}

	if (this->VAO) {
		glDeleteVertexArrays(1, &this->VAO);
	}
}
