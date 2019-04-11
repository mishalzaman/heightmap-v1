#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <sdl/SDL.h>
#include "OpenglSystem.h"
#include "uniform_buffers/UniformBufferMatrices.h"
#include "CameraFP.h"

class Terrein;
class Input;
class UniformBufferMatrices;
class CameraFP;
class SkyBox;
class Light;
class FrameBuffer;

class Engine
{
public:
	Engine(unsigned int width, unsigned int height);
	~Engine();
	void initializeSystem();
	void shutDownSystem();
	void initialize();
	void load();
	void update(float deltaTime);
	void render();
	bool isShutDown();
	SDL_Window* window;
	SDL_GLContext context;
	Input* input;
private:
	// properties
	unsigned int screenWidth;
	unsigned int screenHeight;
	bool shutDown = false;
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
