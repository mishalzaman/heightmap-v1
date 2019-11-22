#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <sdl/SDL.h>
#include "utilities/OpenglSystem.h"
#include "uniform_buffers/UniformBufferMatrices.h"
#include "CameraFP.h"

class Terrein;
class Input;
class UniformBufferMatrices;
class CameraFP;
class SkyBox;
class Light;
class Water;
class FrameBuffer;

class Engine
{
public:
	Engine(unsigned int width, unsigned int height);
	~Engine();
	void cleanUp();
	void initialize(SDL_Window* window);
	void load();
	void update(float deltaTime);
	void render();
	bool isShutDown();
	Input* input;
private:
	// properties
	unsigned int screenWidth;
	unsigned int screenHeight;
	bool shutDown = false;
	SDL_Window* window;
	Terrein* terrein;
	UniformBufferMatrices* uniformBufferMatrices;
	CameraFP* camera;
	SkyBox* skybox;
	Light* light;
	FrameBuffer* framebuffer;
	glm::mat4 projection;
	glm::mat4 view;
};

#endif
