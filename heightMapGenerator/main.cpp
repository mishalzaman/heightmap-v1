#include <iostream>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include "utilities/OpenglSystem.h"
#include "Engine.h"
#include "utilities/GUI.h"

const int width = 1280;
const int height = 720;
const int MINIMUM_FPS_FRAME = 6;
float minimum_fps_delta_time = 1000 / MINIMUM_FPS_FRAME;
float previous_timestep = SDL_GetTicks();
Engine engine = Engine(width, height);

int main(int argc, char *argv[])
{
	// Initialize OpenGl/SDL subsystem
	OpenglSystem::initSDL();
	SDL_Window* window = OpenglSystem::initWindow(width, height);
	SDL_GLContext context = OpenglSystem::initContext(window);
	OpenglSystem::initGlew();
	OpenglSystem::initGlAttributes(3, 3);
	OpenglSystem::enableMouseCursor(false);
	OpenglSystem::enableMouseCapture(true);
	OpenglSystem::setMouseToCenter(window, width, height);
	OpenglSystem::enableDepthTest(true);

	engine.initialize(window);
	engine.load();

	GUI::initImgui(window, context);

	float deltaTime, lastTime = 0.0f;

	while (!engine.isShutDown())
	{
		float current_timestep = SDL_GetTicks();
		
		if (previous_timestep < current_timestep) {

			float deltaTime = current_timestep - previous_timestep;

			if (deltaTime > minimum_fps_delta_time) {
				deltaTime = minimum_fps_delta_time; // slow down if the computer is too slow
			}

			// update
			engine.update(deltaTime);

			previous_timestep = current_timestep;

			// render
			GUI::initImguiFrame(window);

			// GUI::draw();

			engine.render();
			GUI::renderGUI();

			SDL_GL_SwapWindow(window);
		}
		else {
			SDL_Delay(1);
		}

	}

	engine.cleanUp();
	OpenglSystem::cleanUp(context, window);
	GUI::cleanup();

	return 0;
}