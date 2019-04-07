
#include <iostream>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include "Engine.h"

const int width = 1280;
const int height = 720;
Engine* engine = new Engine(width, height);

int main(int argc, char *argv[])
{
	engine->initializeSystem();
	engine->initialize();
	engine->load();

	float deltaTime, lastTime = 0.0f;

	while (!engine->isShutDown())
	{
		float currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		engine->update(deltaTime);
		engine->render();
	}

	engine->shutDownSystem();

	return 0;
}