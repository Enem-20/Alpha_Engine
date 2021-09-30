#include "Input.h"
#include "../Renderer/Renderer.h"
#include "../UI/WindowManager.h"
#include "../Scene/Hierarchy.h"

#include "../UI/Window.h"

#include <GLFW/glfw3.h>

std::list<sol::function> Input::OnClicks;

void Input::glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
	int state = glfwGetMouseButton(WindowManager::CurrentWindow->window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		OnClick();
	}
}

void Input::glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	WindowManager::GetWindow("MainWindow");

	WindowManager::CurrentWindow->size.x = width;
	WindowManager::CurrentWindow->size.y = height;

	if (width > height)
	{
		RenderEngine::Renderer::ViewportOffset.x  = (width - height) / 2;
		RenderEngine::Renderer::ViewportOffset.y = 0;
		width = height;
	}
	else if (height > width)
	{
		RenderEngine::Renderer::ViewportOffset.y = (height - width) / 2;
		RenderEngine::Renderer::ViewportOffset.x = 0;
		height = width;
	}

	RenderEngine::Renderer::ViewportSize.x = width;
	RenderEngine::Renderer::ViewportSize.y = height;

	RenderEngine::Renderer::setViewport(width, height , RenderEngine::Renderer::ViewportOffset.x, RenderEngine::Renderer::ViewportOffset.y);
}

void Input::glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Input::SetCallBacks(GLFWwindow* window)
{
	glfwSetWindowSizeCallback(window, Input::glfwWindowSizeCallBack);
	glfwSetKeyCallback(window, Input::glfwKeyCallBack);
	glfwSetMouseButtonCallback(window, Input::glfwMouseCallBack);
}

void Input::OnClick()
{
	for (auto& it : OnClicks)
	{
		it();
	}
}

void Input::AddListener(const sol::function& func)
{
	OnClicks.push_back(func);
}

glm::ivec2 Input::GetCellReal()
{
	glm::dvec2 cursorPos_OnClick;
	glfwGetCursorPos(WindowManager::CurrentWindow->window, &cursorPos_OnClick.x, &cursorPos_OnClick.y);


	int board_pos_x = cursorPos_OnClick.x - RenderEngine::Renderer::ViewportOffset.x;
	int board_pos_y = RenderEngine::Renderer::ViewportSize.y - cursorPos_OnClick.y + RenderEngine::Renderer::ViewportOffset.y;

	glm::ivec2 res(-9,-9);
	if (board_pos_x >= 0 && board_pos_x < RenderEngine::Renderer::ViewportSize.x && board_pos_y >= 0 && board_pos_y < RenderEngine::Renderer::ViewportSize.x)
	{
		unsigned int cellSize = ((unsigned int)RenderEngine::Renderer::ViewportSize.x >> 3);
		res.x = std::min(board_pos_x / cellSize, 7u);
		res.y = std::min(board_pos_y / cellSize, 7u);
		//std::cout << "cell (" << cell_x << ", " << cell_y << ")" << std::endl;
	}
	return res;
}

glm::ivec2 Input::GetCell(const glm::vec2& objPos)
{
	int board_pos_x = objPos.x - RenderEngine::Renderer::ViewportOffset.x;
	int board_pos_y = objPos.y - RenderEngine::Renderer::ViewportOffset.y;

	glm::ivec2 res(0);
	if (board_pos_x >= 0 && board_pos_x < RenderEngine::Renderer::ViewportSize.x && board_pos_y >= 0 && board_pos_y < RenderEngine::Renderer::ViewportSize.x)
	{
		unsigned int cellSize = ((unsigned int)RenderEngine::Renderer::ViewportSize.x >> 3);
		res.x = std::min(board_pos_x / cellSize, 7u);
		res.y = std::min(board_pos_y / cellSize, 7u);
		//std::cout << "cell (" << cell_x << ", " << cell_y << ")" << std::endl;
	}
	return res;
}