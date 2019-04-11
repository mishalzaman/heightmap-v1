
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <GL/glew.h>
#include <sdl/SDL.h>
#include "Engine.h"

const int width = 1280;
const int height = 720;
Engine* engine = new Engine(width, height);

int main(int argc, char *argv[])
{
	engine->initializeSystem();
	engine->initialize();
	engine->load();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(engine->window, engine->context);
	ImGui_ImplOpenGL3_Init("#version 330");

	bool show_demo_window = true;

	float deltaTime, lastTime = 0.0f;

	while (!engine->isShutDown())
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(engine->window);
		ImGui::NewFrame();

		float currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		engine->update(deltaTime);
		
		// Rendering
		ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Render();
		SDL_GL_MakeCurrent(engine->window, engine->context);

		engine->render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		SDL_GL_SwapWindow(engine->window);
	}

	engine->shutDownSystem();

	//imgui shutdown
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return 0;
}