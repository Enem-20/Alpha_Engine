#include "Window.h"

#ifdef OGL
#include <GLFW/glfw3.h>

GLFWwindow* Window::GetRaw()
{
	return window;
}

Window::Window(GLFWwindow*&& window)
{
	this->window = window;
}

Window::Window()
{
	window = nullptr;
	size = glm::vec2(0.f, 0.f);
}

Window::Window(std::string name, int width, int height)
{
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	size.x = width; size.y = height;
}

void Window::SetWindow(GLFWwindow* window)
{
	this->window = window;
	int width, height;

	glfwGetWindowSize(this->window, &width, &height);
	size.x = width;
	size.y = height;
}

std::shared_ptr<Window> Window::CreateWindow(std::string name, int width, int height)
{
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	size.x = width; size.y = height;
	return std::make_shared<Window>(*this);
}
#endif