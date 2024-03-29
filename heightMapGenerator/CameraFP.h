/*
CameraFP

A camera/view class that acts like an FPS camera.
*/

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class CameraFP
{
public:
	CameraFP(int scrn_width, int scrn_height);
	~CameraFP();
	glm::mat4 getViewMatrix();
	void forward(float deltaTime);
	void backward(float deltaTime);
	void strafeRight(float deltaTime);
	void strafeLeft(float deltaTime);
	void mousePositionUpdate(float deltaTime, int x, int y);
	glm::vec3 getCameraPosition();
private:
	float speed = 0.05f;
	float mouseSensitivity = 0.2f;
	int screenWidthMid;
	int screenHeightMid;

	float yaw = -90.0f; // this is typicall where the view faces towards. -90 degrees is facing towards the z axis
	float pitch = -46.0f;

	glm::vec3 position = glm::vec3(0.0f, 16.0f, 16.0f); // position of camera in the world
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 frontVector;
	glm::vec3 rightVector;
	glm::vec3 upVector;

	void updateVectors();
};

