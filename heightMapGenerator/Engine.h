#ifndef ENGINE_H
#define ENGINE_H

#include <GL/glew.h>
#include <sdl/SDL.h>
#include "OpenglSystem.h"
#include "UniformBufferMatrices.h"
#include "CameraFP.h"

class Terrein;
class Input;
class UniformBufferMatrices;
class CameraFP;
class SkyBox;

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
private:
	// properties
	unsigned int screenWidth;
	unsigned int screenHeight;
	bool shutDown = false;
	SDL_GLContext context;
	Terrein* terrein;
	Input* input;
	UniformBufferMatrices* uniformBufferMatrices;
	CameraFP* camera;
	SkyBox* skybox;
	glm::mat4 projection;
	glm::mat4 view;
};

#endif
