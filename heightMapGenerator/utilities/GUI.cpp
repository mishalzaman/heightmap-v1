#include "GUI.h"

void GUI::initImgui(SDL_Window* window, SDL_GLContext context)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplSDL2_InitForOpenGL(window, context);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void GUI::initImguiFrame(SDL_Window * window)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window);
	ImGui::NewFrame();
}

void GUI::drawDemo()
{
	bool show_demo_window = true;
	ImGui::ShowDemoWindow(&show_demo_window);
}

void GUI::draw()
{
	ImGui::Text("Hello, world %d", 123);
	if (ImGui::Button("Submit"))
	{
		// do stuff
	}
}

void GUI::renderGUI()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::cleanup()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}
