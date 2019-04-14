#include <iostream>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include "Engine.h"
#include "utilities/GUI.h"

const int width = 1280;
const int height = 720;
const int MINIMUM_FPS_FRAME = 6;
float minimum_fps_delta_time = 1000 / MINIMUM_FPS_FRAME;
float previous_timestep = SDL_GetTicks();
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
		float current_timestep = SDL_GetTicks();
		
		if (previous_timestep < current_timestep) {

			float deltaTime = current_timestep - previous_timestep;

			if (deltaTime > minimum_fps_delta_time) {
				deltaTime = minimum_fps_delta_time; // slow down if the computer is too slow
			}

			// update
			engine->update(deltaTime);

			previous_timestep = current_timestep;

			// render
			GUI::initImguiFrame(engine->window);

			// GUI::draw();

			engine->render();
			GUI::renderGUI();

			SDL_GL_SwapWindow(engine->window);
		}
		else {
			SDL_Delay(1);
		}

	}

	engine->shutDownSystem();

	//imgui shutdown
	GUI::cleanup();

	return 0;
}