#include "WindowManager.h"

#include "Window.h"
#include "../Input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

#include <iostream>

std::unordered_map<std::string, std::shared_ptr<Window>> WindowManager::windows;
std::shared_ptr<Window> WindowManager::CurrentWindow;

std::shared_ptr<Window> WindowManager::GetWindow(std::string name)
{
	std::shared_ptr<Window> window = windows.find(name)->second;
	return window ? window : nullptr;
}

void WindowManager::AddWindow(std::string name, int width, int height)
{
	if (CurrentWindow != nullptr)
	{
		CurrentWindow->CreateWindow(name, width, height);

		Input::SetCallBacks(CurrentWindow->window);
		glfwMakeContextCurrent(CurrentWindow->window);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		//ImGui_ImplOpenGL3_Init();
	}
	else
	{
		CurrentWindow = std::make_shared<Window>(name, width, height);
		Input::SetCallBacks(CurrentWindow->window);
		glfwMakeContextCurrent(CurrentWindow->window);
		if (!gladLoadGL())
		{
			std::cout << "Error. glad is not initialized" << std::endl;
			glfwTerminate();
			system("pause");
		}
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		if(windows.size() < 2)
			ImGui_ImplOpenGL3_Init();
	}

	if (!CurrentWindow->window)
	{
		glfwTerminate();
		std::cout << "MainWindow is not created!" << std::endl;
		system("pause");
	}

	windows.emplace(name, CurrentWindow);
}

void WindowManager::Update()
{
	for (auto& window : windows)
	{
		window.second->Update();
	}
}