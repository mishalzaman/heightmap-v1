#include "Engine.h"
#include "Terrein.h"
#include "Input.h"
#include "SkyBox.h"
#include "Light.h"
#include "FrameBuffer.h"

Engine::Engine(unsigned int width, unsigned int height)
{
	this->screenWidth = width;
	this->screenHeight = height;
}

Engine::~Engine()
{
}

void Engine::cleanUp()
{
	delete this->terrein;
	delete this->camera;
	delete this->input;
	delete this->skybox;
	delete this->light;
	delete this->framebuffer;
	delete this->uniformBufferMatrices;
}

void Engine::initialize(SDL_Window* window)
{
	this->window = window;
	this->terrein = new Terrein();
	this->input = new Input();
	this->uniformBufferMatrices = new UniformBufferMatrices();
	this->camera = new CameraFP(this->screenWidth, this->screenHeight);
	this->skybox = new SkyBox();
	this->light = new Light(glm::vec3(40, 10, 40));
	this->framebuffer = new FrameBuffer(this->screenWidth, this->screenHeight);
}

void Engine::load()
{
	this->projection = glm::perspective(glm::radians(45.0f), (float)this->screenWidth / (float)this->screenHeight, 0.1f, 100.0f);
	this->uniformBufferMatrices->updateUBOMatricesProjection(projection);
	this->skybox->load();
	this->terrein->load();
	this->light->load();
	this->framebuffer->load();
}

void Engine::update(float deltaTime)
{
	glm::vec3 lightPosition = this->light->getPosition();

	this->input->update(deltaTime);
	if (this->input->isForward()) { camera->forward(deltaTime); };
	if (this->input->isBackward()) { camera->backward(deltaTime); };
	if (this->input->isStrafeLeft()) { camera->strafeLeft(deltaTime); };
	if (this->input->isStrafeRight()) { camera->strafeRight(deltaTime); };
	if (this->input->isArrowForward()) 
	{ 
		this->light->updatePosition(glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z - 0.1));
	};
	if (this->input->isArrowBackward())
	{
		this->light->updatePosition(glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z + 0.1));
	};
	if (this->input->isArrowLeft())
	{
		this->light->updatePosition(glm::vec3(lightPosition.x - 0.1, lightPosition.y, lightPosition.z));
	};
	if (this->input->isArrowRight())
	{
		this->light->updatePosition(glm::vec3(lightPosition.x + 0.1, lightPosition.y, lightPosition.z));
	};
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
	this->framebuffer->beginDrawingSceneToColourTexture();
		this->terrein->draw(*this->camera, this->light->getPosition());
		this->light->draw();
		this->skybox->draw();
	this->framebuffer->BindToFrameBuffer();
	
	this->framebuffer->render();
}

bool Engine::isShutDown()
{
	return this->shutDown;
}

