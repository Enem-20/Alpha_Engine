#include "WindowManager.h"

#include "../Input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	(CurrentWindow != nullptr) ? CurrentWindow->CreateWindow(name, width, height) : CurrentWindow = std::make_shared<Window>(name, width, height);
	if (!CurrentWindow->window)
	{
		glfwTerminate();
		std::cout << "MainWindow is not created!" << std::endl;
		system("pause");
	}
	Input::SetCallBacks(CurrentWindow->window);

	glfwMakeContextCurrent(CurrentWindow->window);

	windows.emplace(name, CurrentWindow);
}