#include "Input.h"
#include "../GameTypes/Game.h"
#include "../Renderer/Renderer.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/vec2.hpp"
size_t cell_x;
size_t cell_y;
unsigned int g_board_left_offset = 0;
unsigned int g_board_bottom_offset = 0;
glm::ivec2 g_MainWindow_size(1080, 1080);
glm::ivec2 g_BoardSize(g_MainWindow_size);



void Input::glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		glm::dvec2 cursorPos_OnClick;
		glfwGetCursorPos(window, &cursorPos_OnClick.x, &cursorPos_OnClick.y);

		int board_pos_x = cursorPos_OnClick.x - g_board_left_offset;
		int board_pos_y = g_BoardSize.y - cursorPos_OnClick.y + g_board_bottom_offset;

		if (board_pos_x >= 0 && board_pos_x < g_BoardSize.x && board_pos_y >= 0 && board_pos_y < g_BoardSize.x)
		{
			unsigned int cellSize = (g_BoardSize.x >> 3);
			cell_x = std::min(board_pos_x / cellSize, 7u);
			cell_y = std::min(board_pos_y / cellSize, 7u);
			std::cout << "cell (" << cell_x << ", " << cell_y << ")" << std::endl;
			OnClick();
		}
	}
}

void Input::glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	g_MainWindow_size.x = width;
	g_MainWindow_size.y = height;

	if (width > height)
	{
		g_board_left_offset = (width - height) / 2;
		width = height;
	}
	else if (height > width)
	{
		g_board_bottom_offset = (height - width) / 2;
		height = width;
	}

	g_BoardSize.x = width;
	g_BoardSize.y = height;

	RenderEngine::Renderer::setViewport(g_board_left_offset, g_board_bottom_offset, g_BoardSize.x, g_BoardSize.y);

	Game::setBoardSize(g_BoardSize);
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
	if (Game::ECurrentFractinMove == Game::EGameFractionMove::White)
	{
		if (Game::BoardGraph[cell_x][cell_y] == 1)
		{
			if (selected_object != nullptr)
			{
				for (auto it : selected_object->allowedCell)
				{
					Game::BoardGraph[it->cellposition.x][it->cellposition.y] = 0;
				}
				selected_object->allowedCell.clear();
			}
			for (auto it : Game::figures_white)
			{
				if (it.second->cellposition.x == cell_x && it.second->cellposition.y == cell_y)
				{
					selected_object = it.second;
					it.second->Search_path(glm::ivec2(cell_x, cell_y), 1);
				}
			}
		}
		else if (Game::BoardGraph[cell_x][cell_y] == 3)
		{
			for (auto it : selected_object->allowedCell)
			{
				Game::BoardGraph[it->cellposition.x][it->cellposition.y] = 0;
			}
			Game::BoardGraph[cell_x][cell_y] = selected_object->fraction;
			Game::BoardGraph[selected_object->cellposition.x][selected_object->cellposition.y] = 0;
			selected_object->Translate(glm::vec3(cell_x, cell_y, 0));
			selected_object->allowedCell.clear();
			selected_object = nullptr;
			Game::ECurrentFractinMove = Game::EGameFractionMove::Black;
			++Game::Moves_count_white;

			Game::ai.Go();
			//Game::ai.CollectMoves();
		}
	}
}