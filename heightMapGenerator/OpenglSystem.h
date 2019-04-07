#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H

#include <GL/glew.h>
#include <sdl/SDL.h>
#include <iostream>

// https://docs.microsoft.com/en-us/cpp/cpp/namespaces-cpp?view=vs-2017

namespace OpenglSystem {
	void initSDL();
	SDL_Window* initWindow(int width, int height);
	SDL_GLContext initContext(SDL_Window* window);
	void initGlew();
	void initGlAttributes(unsigned int major, unsigned int minor);
	void cleanUp(SDL_GLContext context, SDL_Window* window);
	void enableMouseCapture(bool state);
	void enableMouseCursor(bool state);
	void enableDepthTest(bool state);
	void setMouseToCenter(SDL_Window* window, unsigned int width, unsigned int height);
	void enableWireframe(bool state);
	void enableCulling(bool state);
}

#endif

