#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include <sdl/SDL.h>
#include <iostream>

class Input
{
public:
	Input();
	~Input();
	int mouseX;
	int mouseY;
	void update(float deltaTime);
	bool isForward();
	bool isBackward();
	bool isStrafeLeft();
	bool isStrafeRight();
	bool isArrowForward();
	bool isArrowBackward();
	bool isArrowLeft();
	bool isArrowRight();
	bool isMouseMotion();
	bool isTab();
	bool isQuit();
private:
	SDL_Event event;
	bool forward = false;
	bool backward = false;
	bool strafeRight = false;
	bool strafeLeft = false;
	bool arrowForward = false;
	bool arrowBackward = false;
	bool arrowLeft = false;
	bool arrowRight = false;
	bool mouseMotion = false;
	bool tab = false;
	bool quit = false;
};

