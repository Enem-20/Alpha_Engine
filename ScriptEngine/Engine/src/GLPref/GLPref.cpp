#include "GLPref.h"
#include "../Renderer/Renderer.h"
#include "../UI/WindowManager.h"
#include "../UI/Window.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"

void GLPref::glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}


int GLPref::init()
{
	glm::ivec2 g_MainWindow_size(1080, 1080);
	glm::ivec2 g_BoardSize(g_MainWindow_size);
	glfwSetErrorCallback(&glfwError);
	if (!glfwInit())
	{
		std::cout << "GLFW is not initialized!" << std::endl;
		system("pause");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

#ifdef MAC
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	if (WindowManager::init("MainWindow")) { return -1; }
	Renderer::setViewport(1080,1080,0,0);

	Renderer::setClearColor(0.f, 0.f, 0.f, 1.f);
	std::cout << "Renderer: " << Renderer::getRendererStr() << std::endl;
	std::cout << "OpenGL version: " << Renderer::getVersionStr() << std::endl;
	return 0;
}

void GLPref::PollEvents()
{
	glfwPollEvents();
}

void GLPref::SwapBuffers()
{
	//glfwSwapBuffers(WindowManager::CurrentWindow->window);
}

bool GLPref::isNeedClose()
{
	return glfwWindowShouldClose(WindowManager::CurrentWindow->window);
}

void GLPref::ClearScreenWithBufferColor() {
	glClear(GL_COLOR_BUFFER_BIT);
}