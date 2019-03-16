
#include <iostream>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include "Engine.h"

const int width = 640;
const int height = 480;
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

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		engine->update(deltaTime);
		engine->render();

		SDL_GL_SwapWindow(engine->window);
	}

	engine->shutDownSystem();

	return 0;
}