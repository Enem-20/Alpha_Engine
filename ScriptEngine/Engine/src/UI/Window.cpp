#include "Window.h"

#include "../Input/Input.h"
#include "UIelement.h"

#ifdef OGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>

GLFWwindow* Window::GetRaw()
{
	return window;
}

Window::Window(GLFWwindow* window)
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
	window = nullptr;
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

std::shared_ptr<Window> Window::CreateWindow(const std::string& name, const unsigned int& width, const unsigned int& height)
{
	window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	size.x = width; size.y = height;
	return std::make_shared<Window>(*this);
}

void Window::Awake()
{

}

void Window::Start()
{
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize.x = static_cast<float>(size.x);
	io.DisplaySize.y = static_cast<float>(size.y);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow();
	for (auto& it : UIs)
	{
		it.second->Start();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

void Window::Update()
{
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize.x = static_cast<float>(size.x);
	io.DisplaySize.y = static_cast<float>(size.y);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	for (auto& it : UIs)
	{
		it.second->Update();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

void Window::FixedUpdate()
{

}

std::shared_ptr<UI::Button>& Window::AddUI(const UI::Button& ui)
{
	std::shared_ptr<UI::Button> but = std::make_shared<UI::Button>(ui);
	UIs.emplace(ui.name,but);
	return but;
}

std::shared_ptr<UI::UIelement> Window::GetUI(const std::string& name) const
{
	auto element = UIs.find(name);

	if (element != UIs.end())
	{
		return element->second;
	}

	return nullptr;
}

void Window::RemoveUI(const std::string name)
{
	if(UIs.contains(name))
	{
		UIs.erase(name);
	}
}
#endif