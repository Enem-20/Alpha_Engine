#include "GLPref.h"
#include "../Game/Game.h"
#include "../Resources/ResourceManager.h"

size_t cell_x;
size_t cell_y;
unsigned int g_board_left_offset = 0;
unsigned int g_board_bottom_offset = 0;
glm::ivec2 g_MainWindow_size(1080, 1080);
glm::ivec2 g_BoardSize(g_MainWindow_size);

void GLPref::glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods)
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

			if (Game::BoardGraph[cell_x][cell_y] == 1)
			{
				for (auto it : Game::fl_GObjects)
				{
					
				}
			}
		}
	}
}

void GLPref::glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
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

	glViewport(g_board_left_offset, g_board_bottom_offset, g_BoardSize.x, g_BoardSize.y);

	Game::setBoardSize(g_BoardSize);
}

void GLPref::glfwError(int id, const char* description)
{
	std::cout << description << std::endl;
}

void GLPref::glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	Game::setKey(key, action);
}

int GLPref::init()
{
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

	Mainwindow = glfwCreateWindow(g_MainWindow_size.x, g_MainWindow_size.y, "MoveChess", nullptr, nullptr);
	if (!Mainwindow)
	{
		glfwTerminate();
		std::cout << "MainWindow is not created!" << std::endl;
		system("pause");
		return -1;
	}

	glfwSetWindowSizeCallback(Mainwindow, glfwWindowSizeCallBack);
	glfwSetKeyCallback(Mainwindow, glfwKeyCallBack);
	glfwSetMouseButtonCallback(Mainwindow, glfwMouseCallBack);

	glfwMakeContextCurrent(Mainwindow);

	if (!gladLoadGL())
	{
		std::cout << "Error. glad is not initialized" << std::endl;
		glfwTerminate();
		system("pause");
		return -1;
	}

	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.f, 0.f, 0.f, 1.f);
	//AllowedCell allowedCells[8];
	//for (unsigned int divide = 8u; divide > 0; --divide)
	//{
	//	allowedCells[divide - 1].SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", g_BoardSize.x / 8u, g_BoardSize.y / 8u, "");
	//	allowedCells[divide - 1].Translate(glm::ivec3(g_BoardSize.x / divide, 0, 0));
	//}
	/*AllowedCell allowedCell1;
	allowedCell1.SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", g_BoardSize.x / 8u, g_BoardSize.y / 8u, "");
	AllowedCell allowedCell2;
	allowedCell2.SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", g_BoardSize.x / 8u, g_BoardSize.y / 8u, "");*/


	//allowedCell2.Translate(glm::vec3(1, 1, 0));
}