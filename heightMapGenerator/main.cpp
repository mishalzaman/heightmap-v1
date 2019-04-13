#include <iostream>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include "Engine.h"
#include "utilities/GUI.h"

const int width = 1280;
const int height = 720;
Engine* engine = new Engine(width, height);

int main(int argc, char *argv[])
{
	engine->initializeSystem();
	engine->initialize();
	engine->load();

	GUI::initImgui(engine->window, engine->context);

	float deltaTime, lastTime = 0.0f;

	while (!engine->isShutDown())
	{
		// Start the Dear ImGui frame
		GUI::initImguiFrame(engine->window);

		float currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		engine->update(deltaTime);
		
		// Rendering
		// GUI::draw();

		engine->render();
		GUI::renderGUI();
		
		SDL_GL_SwapWindow(engine->window);
	}

	engine->shutDownSystem();

	//imgui shutdown
	GUI::cleanup();

	return 0;
}