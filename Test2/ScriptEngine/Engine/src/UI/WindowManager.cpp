#include "WindowManager.h"

#include "Window.h"
#include "../Input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Window>> WindowManager::windows;
std::shared_ptr<Window> WindowManager::CurrentWindow;

std::shared_ptr<Window> WindowManager::GetWindow(std::string name)
{
	std::shared_ptr<Window> window = windows.find(name)->second;
	return window ? window : nullptr;
}

int WindowManager::init(std::string name, int width, int height)
{
	CurrentWindow = std::make_shared<Window>(name, width, height);
	Input::SetCallBacks(CurrentWindow->window);
	glfwMakeContextCurrent(CurrentWindow->window);
	if (!gladLoadGL())
	{
		std::cout << "Error. glad is not initialized" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplGlfw_InitForOpenGL(CurrentWindow->GetRaw(),true);

	windows.emplace(std::move(name), CurrentWindow);

	return 0;
}

std::shared_ptr<Window> WindowManager::AddWindow(std::string name, int width, int height)
{
	if (CurrentWindow != nullptr)
	{
		CurrentWindow->CreateWindow(name, width, height);

		Input::SetCallBacks(CurrentWindow->window);
		glfwMakeContextCurrent(CurrentWindow->window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
	}
	else
	{
		CurrentWindow = std::make_shared<Window>(name, width, height);
		Input::SetCallBacks(CurrentWindow->window);
		glfwMakeContextCurrent(CurrentWindow->window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
	}

	if (!CurrentWindow->window)
	{
		glfwTerminate();
		std::cout << "Window " << name <<  " is not created!" << std::endl;
		system("pause");
	}

	windows.emplace(name, CurrentWindow);

	return CurrentWindow;
}

void WindowManager::Start()
{
	for (auto& window : windows)
	{
		window.second->Start();
	}
}

void WindowManager::Update()
{
	for (auto& window : windows)
	{
		window.second->Update();
	}
}