#include "Plane.h"

Plane::Plane(int width, int height)
{
	this->width = width;
	this->height = height;

	this->generateVerticesAndTextureCoordinates();
	this->generateIndices();
	this->generateNormals();
}

Plane::~Plane()
{
}

std::vector<MeshStruct> Plane::getMesh()
{
	return this->mesh;
}

std::vector<glm::uvec3> Plane::getIndices()
{
	return this->indices;
}

void Plane::generateVerticesAndTextureCoordinates()
{
	for (int row = 0; row <= this->height; row++)
	{
		for (int column = 0; column <= this->width; column++)
		{
			MeshStruct mesh;

			float x = (float)column / (float)this->width;
			float y = (float)row / (float)this->height;
			float z = 0.0f;

			mesh.position = glm::vec3(x, y, z);
			mesh.texture = glm::vec2(x, y);
			this->mesh.push_back(mesh);
		}
	}
}

void Plane::generateIndices()
{
	for (int row = 0; row < this->height; row++)
	{
		for (int column = 0; column < this->width; column++)
		{
			int row1 = row * (this->width + 1);
			int row2 = (row + 1) * (this->width + 1);

			// triangle 1
			this->indices.push_back(glm::uvec3(row1 + column, row1 + column + 1, row2 + column + 1));

			// triangle 2
			this->indices.push_back(glm::uvec3(row1 + column, row2 + column + 1, row2 + column));
		}
	}
}

void Plane::generateNormals()
{
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
}
