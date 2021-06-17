#include "Input.h"
#include "../Renderer/Renderer.h"
#include "../UI/WindowManager.h"
#include "../Renderer/Renderer.h"
#include "../Resources/ResourceManager.h"

#include <coroutine>
#include <iostream>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/vec2.hpp"
#include <glm/gtc/matrix_transform.hpp>


size_t cell_x;
size_t cell_y;
unsigned int g_board_left_offset = 0;
unsigned int g_board_bottom_offset = 0;
glm::ivec2 g_MainWindow_size(1080, 1080);
glm::ivec2 g_BoardSize(g_MainWindow_size);

std::map<Input::Keys, int> Input::GlEqKeys = 
{
		{ key0, GLFW_KEY_0 },
		{ key1, GLFW_KEY_1 },
		{ key2, GLFW_KEY_2 },
		{ key3, GLFW_KEY_3 },
		{ key4, GLFW_KEY_4 },
		{ key5, GLFW_KEY_5 },
		{ key6, GLFW_KEY_6 },
		{ key7, GLFW_KEY_7 },
		{ key8, GLFW_KEY_8 },
		{ key9, GLFW_KEY_9 },
		/*{keyN0, GLFW_key_},
		{keyM1,},
		{keyN2,},
		{keyN3,},
		{keyN4,},
		{keyN5,},
		{keyN6,},
		{keyN7,},
		{keyN8,},
		{keyN9,},*/
		{keyF1, GLFW_KEY_F1},
		{keyF2, GLFW_KEY_F2},
		{keyF3, GLFW_KEY_F3},
		{keyF4, GLFW_KEY_F4},
		{keyF5, GLFW_KEY_F5},
		{keyF6, GLFW_KEY_F6},
		{keyF7, GLFW_KEY_F7},
		{keyF8, GLFW_KEY_F8},
		{keyF9, GLFW_KEY_F9},
		{keyF10,GLFW_KEY_F10},
		{keyF11,GLFW_KEY_F11},
		{keyF12,GLFW_KEY_F12},
		{keyTab,GLFW_KEY_TAB},
		{keyCaps,GLFW_KEY_CAPS_LOCK},
		{keyLShift,GLFW_KEY_LEFT_SHIFT},
		{keyRShift,GLFW_KEY_RIGHT_SHIFT},
		{keyLCtrl,GLFW_KEY_LEFT_CONTROL},
		{keyRCtrl,GLFW_KEY_RIGHT_CONTROL},
		{keyLAlt,GLFW_KEY_LEFT_ALT},
		{keyRAlt,GLFW_KEY_RIGHT_ALT},
		{keyEnter,GLFW_KEY_ENTER},
		{keyBackSpace,GLFW_KEY_BACKSPACE},
		/*{keyLeftArrow,GLFW_KEY_},
		{keyUpArrow,},
		{keyRightArrow,},
		{keyDownArrow,},*/
		{keyQ,GLFW_KEY_Q},
		{keyW,GLFW_KEY_W},
		{keyE,GLFW_KEY_E},
		{keyR,GLFW_KEY_R},
		{keyT,GLFW_KEY_T},
		{keyY,GLFW_KEY_Y},
		{keyU,GLFW_KEY_U},
		{keyI,GLFW_KEY_I},
		{keyO,GLFW_KEY_O},
		{keyP,GLFW_KEY_P},
		{keyA,GLFW_KEY_A},
		{keyS,GLFW_KEY_S},
		{keyD,GLFW_KEY_D},
		{keyF,GLFW_KEY_F},
		{keyG,GLFW_KEY_G},
		{keyH,GLFW_KEY_H},
		{keyJ,GLFW_KEY_J},
		{keyK,GLFW_KEY_K},
		{keyL,GLFW_KEY_L},
		{keyZ,GLFW_KEY_Z},
		{keyX,GLFW_KEY_X},
		{keyC,GLFW_KEY_C},
		{keyV,GLFW_KEY_V},
		{keyB,GLFW_KEY_B},
		{keyN,GLFW_KEY_N},
		{keyM, GLFW_KEY_M} 
};

Input::UIs Input::UIElements;

bool Input::KeyStates[71] = { false };
bool Input::KeyStatesPrev[71] = { false };

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
		}
		OnClick(cursorPos_OnClick);
	}
}

void Input::glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	WindowManager::GetWindow("MainWindow");

	WindowManager::CurrentWindow->size.x = width;
	WindowManager::CurrentWindow->size.y = height;

	if (width > height)
	{
		g_board_left_offset = (width - height) / 2;
		g_board_bottom_offset = 0;
		width = height;
	}
	else if (height > width)
	{
		g_board_bottom_offset = (height - width) / 2;
		g_board_left_offset = 0;
		height = width;
	}

	g_BoardSize.x = width;
	g_BoardSize.y = height;

	RenderEngine::Renderer::setViewport(width, height , g_board_left_offset, g_board_bottom_offset);
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

void Input::OnClick(const glm::dvec2& mousePos)
{
	glm::dvec2 ConvertmousePos = glm::dvec2(mousePos.x, RenderEngine::Renderer::ViewportSize.y - mousePos.y - 21);
	if (ConvertmousePos.y < 0.f)
	{
		ConvertmousePos.y *= -1;
	}
	auto element = CheckShotUI(std::move(ConvertmousePos));
	if (element != nullptr)
	{
		element->executeOnClicks();
	}
}

std::shared_ptr<UI::UIelement> Input::CheckShotUI(const glm::dvec2& mousePos)
{
	for (auto element : UIElements)
	{
		if (element.second->collider->CheckIntersect(std::move(mousePos)))
		{
			return element.second;
		}
	}

	return nullptr;
}

void Input::AddUI(std::string name, std::shared_ptr<UI::UIelement> UIElement)
{
	UIElements.emplace(name, UIElement);
}

std::shared_ptr<UI::UIelement> Input::GetUI(std::string name)
{
	auto element = UIElements.find(name);

	if (element != UIElements.end())
	{
		return element->second;
	}

	return nullptr;
}

bool Input::GetKeyDown(Keys KeyCode)
{
	return (KeyStates[KeyCode] && !KeyStatesPrev[KeyCode]) ? true : false;
}

bool Input::GetKeyUp(Keys KeyCode)
{
	return (!KeyStates[KeyCode] && KeyStatesPrev[KeyCode]) ? true : false;
}

bool Input::GetKeyStay(Keys KeyCode)
{
	return KeyStates[KeyCode];
}

void Input::Update()
{
	for (size_t i = 0; i < 71; ++i)
	{
		KeyStatesPrev[i] = KeyStates[i];
	}

	for (auto it : UIElements)
	{
		it.second->Update();
	}

	for (size_t i = 0; i < 71; ++i)
	{
		auto key = GlEqKeys.find((Keys)i);

		if(key != GlEqKeys.end()){KeyStates[i] = glfwGetKey(WindowManager::CurrentWindow->window, key->second);}
		
	}
}