#ifndef GUI_H
#define GUI_H

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_opengl3.h"
#include <GL/glew.h>
#include <sdl/SDL.h>

namespace GUI {
	void initImgui(SDL_Window* window, SDL_GLContext context);
	void initImguiFrame(SDL_Window* window);
	void drawDemo();
	void draw();
	void renderGUI();
	void cleanup();
}

#endif