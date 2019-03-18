#include "Engine.h"
#include "Terrein.h"
#include "Input.h"
#include "SkyBox.h"
#include "Lamp.h"

Engine::Engine(unsigned int width, unsigned int height)
{
	this->screenWidth = width;
	this->screenHeight = height;
}

Engine::~Engine()
{
}

void Engine::initializeSystem()
{
	OpenglSystem::initSDL();
	this->window = OpenglSystem::initWindow(this->screenWidth, this->screenHeight);
	this->context = OpenglSystem::initContext(this->window);
	OpenglSystem::initGlew();
	OpenglSystem::initGlAttributes(3, 3);
	OpenglSystem::enableMouseCursor(false);
	OpenglSystem::enableMouseCapture(true);
	OpenglSystem::setMouseToCenter(this->window, this->screenWidth, this->screenHeight);
	OpenglSystem::enableDepthTest(true);
}

void Engine::shutDownSystem()
{
	OpenglSystem::cleanUp(this->context, this->window);
}

void Engine::initialize()
{
	this->terrein = new Terrein();
	this->input = new Input();
	this->uniformBufferMatrices = new UniformBufferMatrices();
	this->camera = new CameraFP(this->screenWidth, this->screenHeight);
	this->skybox = new SkyBox();
	this->lamp = new Lamp();
}

void Engine::load()
{
	this->projection = glm::perspective(glm::radians(45.0f), (float)this->screenWidth / (float)this->screenHeight, 0.1f, 100.0f);
	this->uniformBufferMatrices->updateUBOMatricesProjection(projection);
	this->skybox->load();
	this->terrein->load(64);
	this->lamp->load();
}

void Engine::update(float deltaTime)
{
	this->input->update(deltaTime);
	if (this->input->isForward()) { camera->forward(deltaTime); };
	if (this->input->isBackward()) { camera->backward(deltaTime); };
	if (this->input->isStrafeLeft()) { camera->strafeLeft(deltaTime); };
	if (this->input->isStrafeRight()) { camera->strafeRight(deltaTime); };
	if (this->input->isMouseMotion())
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		camera->mousePositionUpdate(deltaTime, x, y);
		SDL_WarpMouseInWindow(this->window, this->screenWidth / 2.0f, this->screenHeight / 2.0f);
	}
	if (this->input->isQuit()) { this->shutDown = true; }

	this->view = this->camera->getViewMatrix();
	this->uniformBufferMatrices->updateUBOMatricesView(view);
}

void Engine::render()
{
	this->skybox->draw();
	// OpenglSystem::enableWireframe(true);
	this->terrein->render();
	this->lamp->render();
}

bool Engine::isShutDown()
{
	return this->shutDown;
}
