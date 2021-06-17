#include "GLPref.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/Renderer.h"
#include "../UI/WindowManager.h"

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

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

#ifdef MAC
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	WindowManager::AddWindow("MainWindow", 1080, 1080);

	if (!gladLoadGL())
	{
		std::cout << "Error. glad is not initialized" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	RenderEngine::Renderer::setViewport(1080,1080,0,0);

	RenderEngine::Renderer::setClearColor(0.f, 0.f, 0.f, 1.f);
	std::cout << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;
	std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << std::endl;
}

void GLPref::PollEvents()
{
	glfwPollEvents();
}

void GLPref::SwapBuffers()
{
	glfwSwapBuffers(WindowManager::CurrentWindow->window);
}

bool GLPref::isNeedClose()
{
	return glfwWindowShouldClose(WindowManager::CurrentWindow->window);
}