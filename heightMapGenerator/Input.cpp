#include "Input.h"

using namespace std;

Input::Input()
{
}

Input::~Input()
{
}

void Input::update(float deltaTime)
{
	while (SDL_PollEvent(&this->event)) {
		// Update input events for Imgui
		ImGui_ImplSDL2_ProcessEvent(&event);

		switch (this->event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_w && event.key.repeat == 0) { this->forward = true; }
			if (event.key.keysym.sym == SDLK_s && event.key.repeat == 0) { this->backward = true; }
			if (event.key.keysym.sym == SDLK_a && event.key.repeat == 0) { this->strafeLeft = true; }
			if (event.key.keysym.sym == SDLK_d && event.key.repeat == 0) { this->strafeRight = true; }
			// arrow keys
			if (event.key.keysym.sym == SDLK_UP && event.key.repeat == 0) { this->arrowForward = true; }
			if (event.key.keysym.sym == SDLK_DOWN && event.key.repeat == 0) { this->arrowBackward = true; }
			if (event.key.keysym.sym == SDLK_LEFT && event.key.repeat == 0) { this->arrowLeft = true; }
			if (event.key.keysym.sym == SDLK_RIGHT && event.key.repeat == 0) { this->arrowRight = true; }
			if (event.key.keysym.sym == SDLK_ESCAPE) { this->quit = true; }
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_w && event.key.repeat == 0) { this->forward = false; }
			if (event.key.keysym.sym == SDLK_s && event.key.repeat == 0) { this->backward = false; }
			if (event.key.keysym.sym == SDLK_a && event.key.repeat == 0) { this->strafeLeft = false; }
			if (event.key.keysym.sym == SDLK_d && event.key.repeat == 0) { this->strafeRight = false; }
			// arrow keys
			if (event.key.keysym.sym == SDLK_UP && event.key.repeat == 0) { this->arrowForward = false; }
			if (event.key.keysym.sym == SDLK_DOWN && event.key.repeat == 0) { this->arrowBackward = false; }
			if (event.key.keysym.sym == SDLK_LEFT && event.key.repeat == 0) { this->arrowLeft = false; }
			if (event.key.keysym.sym == SDLK_RIGHT && event.key.repeat == 0) { this->arrowRight = false; }
			break;
		case SDL_MOUSEMOTION:
			this->mouseMotion = true;
		default:
			break;
		}
	}
}

bool Input::isForward() { return this->forward; }
bool Input::isBackward() { return this->backward; }
bool Input::isStrafeLeft() { return this->strafeLeft; }
bool Input::isStrafeRight() { return this->strafeRight; }
bool Input::isArrowForward() { return this->arrowForward; }
bool Input::isArrowBackward() { return this->arrowBackward; }
bool Input::isArrowLeft() { return this->arrowLeft; }
bool Input::isArrowRight() { return this->arrowRight; }
bool Input::isMouseMotion()
{ 
	if (this->mouseMotion)
	{
		this->mouseMotion = false;
		return true;
	}

	return false;
}
bool Input::isQuit() { return this->quit; }

