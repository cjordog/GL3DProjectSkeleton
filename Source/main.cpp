#define GLM_CONFIG_XYZW_ONLY

#include "Window.h"
#include "Input.h"
#include "World.h"
#include "GX.h"
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>

#ifdef IMGUI_ENABLED
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#endif

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

// settings
const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;

int main()
{
	glfwInit();
	Window window(SCR_WIDTH, SCR_HEIGHT);
	if (window.Init() < 0)
	{
		return -1;
	}
	if (GX::GLADInit() < 0)
	{
		return -1;
	}
	Input input(&window);
	World world;
	World::InitShared();
	world.Init();

#ifdef IMGUI_ENABLED
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window.GetGLFWWindow(), true);
	const char* glsl_version = "#version 460";
	ImGui_ImplOpenGL3_Init(glsl_version);
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
#endif

	auto lastFrameTime = std::chrono::high_resolution_clock::now();

	while (!window.ShouldClose())
	{
		FrameMark;
		input.ProcessInput();

		auto currentTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> frameTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;

		world.Update(frameTime.count(), input.GetInputData());
		world.Render();
		GX::SwapBuffers(window.GetGLFWWindow());
		input.Poll();
	}

#ifdef IMGUI_ENABLED
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#endif

	glfwTerminate();
	return 0;
}