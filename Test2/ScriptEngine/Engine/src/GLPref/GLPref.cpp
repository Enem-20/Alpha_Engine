#include "GLPref.h"
#include "../Game/Game.h"
#include "../Resources/ResourceManager.h"
#include "../Input/Input.h"
#include "../Renderer/Renderer.h"

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

	Mainwindow = glfwCreateWindow(g_MainWindow_size.x, g_MainWindow_size.y, "MoveChess", nullptr, nullptr);
	if (!Mainwindow)
	{
		glfwTerminate();
		std::cout << "MainWindow is not created!" << std::endl;
		system("pause");
		return -1;
	}
	Input::SetCallBacks(Mainwindow);

	glfwMakeContextCurrent(Mainwindow);

	if (!gladLoadGL())
	{
		std::cout << "Error. glad is not initialized" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	RenderEngine::Renderer::setClearColor(0.f, 0.f, 0.f, 1.f);
	std::cout << "Renderer: " << RenderEngine::Renderer::getRendererStr() << std::endl;
	std::cout << "OpenGL version: " << RenderEngine::Renderer::getVersionStr() << std::endl;
}