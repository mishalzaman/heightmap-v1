#include <sdl/SDL.h>
#include "Terrein.h"

#include "utilities/OpenglSystem.h"

using namespace std;

Terrein::Terrein(): shader("shaders/material.vert", "shaders/material.frag")
{
	this->shader.setUBOMatrices();
}

Terrein::~Terrein()
{
	this->cleanup();
}

void Terrein::load()
{
	this->mapSize = mapSize;

	this->getHeightMapImageData();
	this->getDIffuseMap();
	this->build();
	stbi_image_free(this->imageData);
	stbi_image_free(this->diffuseData);
}

void Terrein::build()
{
	// https://stackoverflow.com/questions/47086858/create-a-grid-in-opengl
	// https://www.learnopengles.com/tag/height-maps/

	printf("image width %d\n", this->imageWidth);
	printf("image height %d\n", this->imageHeight);

	for (int row = 0; row <= this->imageHeight; row++)
	{
		for (int column = 0; column <= this->imageWidth; column++)
		{
			float x = (float)column / (float)this->imageWidth;
			float y = (float)row / (float)this->imageHeight;

			float z;
			if (row == this->imageHeight || column == this->imageWidth || row == 0 || column == 0)
			{
				z = 0.0f;
			}
			else
			{
				float pixel = this->imageData[this->imageWidth * row + column];
				z = float(pixel / 256.0)*this->scale; 
			}
			
			MeshV3 mesh;
			mesh.position = glm::vec3(x, y, z);
			mesh.normal = glm::vec3(0.0, 0.0, 0.0);
			mesh.texture = glm::vec2(x, y);
			
			this->mesh.push_back(mesh);
			
		}
	}

	for (int row = 0; row < this->imageHeight; row++)
	{
		for (int column = 0; column < this->imageWidth; column++)
		{
			int row1 = row * (this->imageWidth + 1);
			int row2 = (row + 1) * (this->imageWidth + 1);

			// triangle 1
			this->indices.push_back(glm::uvec3(row1 + column, row1 + column + 1, row2 + column + 1));

			// triangle 2
			this->indices.push_back(glm::uvec3(row1 + column, row2 + column + 1, row2 + column));
		}
	}
	
	for (int i = 0; i < this->indices.size(); i++)
	{
		glm::vec3 v1 = this->mesh[this->indices[i].x].position;
		glm::vec3 v2 = this->mesh[this->indices[i].y].position;
		glm::vec3 v3 = this->mesh[this->indices[i].z].position;

		glm::vec3 edge1 = v1 - v2;
		glm::vec3 edge2 = v1 - v3;
		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

		this->mesh[this->indices[i].x].normal += normal;
		this->mesh[this->indices[i].y].normal += normal;
		this->mesh[this->indices[i].z].normal += normal;
	}

	printf("mesh size %d\n", this->mesh.size());
	printf("indices size %d\n", this->indices.size());

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->IBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, this->mesh.size() * sizeof(MeshV3), &this->mesh[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(glm::uvec3), glm::value_ptr(this->indices[0]), GL_STATIC_DRAW);

	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshV3), (void*)0);
	glEnableVertexAttribArray(0);

	// normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshV3), (void*)offsetof(MeshV3, normal));
	glEnableVertexAttribArray(1);

	// textures
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshV3), (void*)offsetof(MeshV3, texture));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Terrein::getHeightMapImageData()
{
	std::string path = "assets/test_heightmap.bmp";
	int nChannels;
	this->imageData = stbi_load(path.c_str(), &this->imageWidth, &this->imageHeight, &nChannels, 1);

	if (!imageData)
	{
		cout << "Coult not load terrein heightmap texture" << endl;
	}
}

void Terrein::getDIffuseMap()
{
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.

	std::string path = "assets/test_diffuse.png";
	this->diffuseData = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (this->diffuseData)
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->diffuseData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load diffuse texture" << std::endl;
	}
}

void Terrein::draw(CameraFP &camera, glm::vec3 lampPosition)
{
	// http://www.rastertek.com/dx11ter02.html
	float scale = 32.0;

	glBindTexture(GL_TEXTURE_2D, this->texture);
	this->shader.use();
	glBindVertexArray(this->VAO);
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
	model = glm::scale(model, glm::vec3(scale, scale, scale));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0, 0.0, 0.0));
	this->shader.setMat4("model", model);

	// light properties
	glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
	this->shader.setVec3("lightColor", lightColor);
	this->shader.setVec3("lightPos", lampPosition);
	this->shader.setVec3("objectColor", glm::vec3(0.4f, 0.4f, 0.4f));

	OpenglSystem::enableCulling(true);
	glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size() * 3, GL_UNSIGNED_INT, 0);
	OpenglSystem::enableCulling(false);
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

void Terrein::setScale(float scale)
{
	this->scale = scale;
}

int Terrein::getWidth()
{
	return this->imageWidth;
}

int Terrein::getHeight()
{
	return this->imageHeight;
}
