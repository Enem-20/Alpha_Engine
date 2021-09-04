#include "Window.h"

#ifdef OGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>

GLFWwindow* Window::GetRaw()
{
	return window;
}

Window::Window(GLFWwindow*&& window)
	:window(std::move(window))
{
	this->window = window;
	glfwGetWindowSize(this->window, &size.x, &size.y);
}

Window::Window()
{
	window = nullptr;
	size = glm::ivec2(0, 0);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	//glfwTerminate();
}

Window::Window(std::string name, int width, int height)
{
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	size.x = width; size.y = height;
}

void Window::SetWindow(GLFWwindow* window)
{
	this->window = window;

	glfwGetWindowSize(this->window, &size.x, &size.y);
}

std::shared_ptr<Window> Window::CreateWindow(std::string name, int width, int height)
{
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	size.x = width; size.y = height;
	return std::make_shared<Window>(*this);
}

void Window::Update()
{
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize.x = static_cast<float>(size.x);
	io.DisplaySize.y = static_cast<float>(size.y);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}
#endif