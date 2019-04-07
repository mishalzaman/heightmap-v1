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
	this->light = new Light(glm::vec3(40, 10, 40));
	this->framebuffer = new FrameBuffer(this->screenWidth, this->screenHeight);
}

void Engine::load()
{
	this->projection = glm::perspective(glm::radians(45.0f), (float)this->screenWidth / (float)this->screenHeight, 0.1f, 100.0f);
	this->uniformBufferMatrices->updateUBOMatricesProjection(projection);
	this->skybox->load();
	this->terrein->load(388);
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
	this->framebuffer->firstPass();
	// OpenglSystem::enableWireframe(true);
	OpenglSystem::enableCulling(true);
	this->terrein->draw(*this->camera, this->light->getPosition());
	OpenglSystem::enableCulling(false);
	this->light->draw();
	this->skybox->draw();
	// OpenglSystem::enableWireframe(false);

	this->framebuffer->secondPass();
	this->framebuffer->render();

	SDL_GL_SwapWindow(this->window);
}

bool Engine::isShutDown()
{
	return this->shutDown;
}
