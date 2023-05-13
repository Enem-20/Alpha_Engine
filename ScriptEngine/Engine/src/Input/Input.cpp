#include "Input.h"
#include "../../internal/Renderer/src/Renderer.h"
#include "../../internal/Renderer/src/WindowManager.h"
#include "../Scene/Hierarchy.h"

#include "../../internal/Renderer/src/Window.h"

#include <GLFW/glfw3.h>

#ifdef OGL
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
		Renderer::ViewportOffset.x  = (width - height) / 2;
		Renderer::ViewportOffset.y = 0;
		width = height;
	}
	else if (height > width)
	{
		Renderer::ViewportOffset.y = (height - width) / 2;
		Renderer::ViewportOffset.x = 0;
		height = width;
	}

	Renderer::ViewportSize.x = width;
	Renderer::ViewportSize.y = height;

	Renderer::setViewport(width, height , Renderer::ViewportOffset.x, Renderer::ViewportOffset.y);
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


	int board_pos_x = static_cast<int>(cursorPos_OnClick.x - Renderer::ViewportOffset.x);
	int board_pos_y = static_cast<int>(Renderer::ViewportSize.y - cursorPos_OnClick.y + Renderer::ViewportOffset.y);

	glm::ivec2 res(-9,-9);
	if (board_pos_x >= 0 && board_pos_x < Renderer::ViewportSize.x && board_pos_y >= 0 && board_pos_y < Renderer::ViewportSize.x)
	{
		unsigned int cellSize = ((unsigned int)Renderer::ViewportSize.x >> 3);
		res.x = std::min(board_pos_x / cellSize, 7u);
		res.y = std::min(board_pos_y / cellSize, 7u);
		//std::cout << "cell (" << cell_x << ", " << cell_y << ")" << std::endl;
	}
	return res;
}

glm::ivec2 Input::GetCell(const glm::vec2& objPos)
{
	int board_pos_x = static_cast<int>(objPos.x - Renderer::ViewportOffset.x);
	int board_pos_y = static_cast<int>(objPos.y - Renderer::ViewportOffset.y);

	glm::ivec2 res(0);
	if (board_pos_x >= 0 && board_pos_x < Renderer::ViewportSize.x && board_pos_y >= 0 && board_pos_y < Renderer::ViewportSize.x)
	{
		unsigned int cellSize = ((unsigned int)Renderer::ViewportSize.x >> 3);
		res.x = std::min(board_pos_x / cellSize, 7u);
		res.y = std::min(board_pos_y / cellSize, 7u);
		//std::cout << "cell (" << cell_x << ", " << cell_y << ")" << std::endl;
	}
	return res;
}

#endif