#include "Input.h"
#include "../Renderer/Renderer.h"
#include "../UI/WindowManager.h"
#include "../Renderer/Renderer.h"
#include "../Resources/ResourceManager.h"
#include "../UI/Window.h"]
#include "../Input/Input.h"

#include <iostream>
//#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

//struct Awaiter {
//	std::coroutine_handle<task::promise_type>* hp_;
//	glm::vec2 pos;
//	GLFWwindow* window;
//	constexpr bool await_ready() const noexcept { return false; }
//	void await_suspend(std::coroutine_handle<task::promise_type> h) { *hp_ = h; }
//	constexpr void await_resume() const noexcept {}
//};

//size_t cell_x;
//size_t cell_y;
//unsigned int g_board_left_offset = 0;
//unsigned int g_board_bottom_offset = 0;
//glm::ivec2 g_MainWindow_size(1080, 1080);
//glm::ivec2 g_BoardSize(g_MainWindow_size);
//
//std::map<Input::Keys, int> Input::GlEqKeys = 
//{
//		{ key0, GLFW_KEY_0 },
//		{ key1, GLFW_KEY_1 },
//		{ key2, GLFW_KEY_2 },
//		{ key3, GLFW_KEY_3 },
//		{ key4, GLFW_KEY_4 },
//		{ key5, GLFW_KEY_5 },
//		{ key6, GLFW_KEY_6 },
//		{ key7, GLFW_KEY_7 },
//		{ key8, GLFW_KEY_8 },
//		{ key9, GLFW_KEY_9 },
//		/*{keyN0, GLFW_key_},
//		{keyM1,},
//		{keyN2,},
//		{keyN3,},
//		{keyN4,},
//		{keyN5,},
//		{keyN6,},
//		{keyN7,},
//		{keyN8,},
//		{keyN9,},*/
//		{keyF1, GLFW_KEY_F1},
//		{keyF2, GLFW_KEY_F2},
//		{keyF3, GLFW_KEY_F3},
//		{keyF4, GLFW_KEY_F4},
//		{keyF5, GLFW_KEY_F5},
//		{keyF6, GLFW_KEY_F6},
//		{keyF7, GLFW_KEY_F7},
//		{keyF8, GLFW_KEY_F8},
//		{keyF9, GLFW_KEY_F9},
//		{keyF10,GLFW_KEY_F10},
//		{keyF11,GLFW_KEY_F11},
//		{keyF12,GLFW_KEY_F12},
//		{keyTab,GLFW_KEY_TAB},
//		{keyCaps,GLFW_KEY_CAPS_LOCK},
//		{keyLShift,GLFW_KEY_LEFT_SHIFT},
//		{keyRShift,GLFW_KEY_RIGHT_SHIFT},
//		{keyLCtrl,GLFW_KEY_LEFT_CONTROL},
//		{keyRCtrl,GLFW_KEY_RIGHT_CONTROL},
//		{keyLAlt,GLFW_KEY_LEFT_ALT},
//		{keyRAlt,GLFW_KEY_RIGHT_ALT},
//		{keyEnter,GLFW_KEY_ENTER},
//		{keyBackSpace,GLFW_KEY_BACKSPACE},
//		/*{keyLeftArrow,GLFW_KEY_},
//		{keyUpArrow,},
//		{keyRightArrow,},
//		{keyDownArrow,},*/
//		{keyQ,GLFW_KEY_Q},
//		{keyW,GLFW_KEY_W},
//		{keyE,GLFW_KEY_E},
//		{keyR,GLFW_KEY_R},
//		{keyT,GLFW_KEY_T},
//		{keyY,GLFW_KEY_Y},
//		{keyU,GLFW_KEY_U},
//		{keyI,GLFW_KEY_I},
//		{keyO,GLFW_KEY_O},
//		{keyP,GLFW_KEY_P},
//		{keyA,GLFW_KEY_A},
//		{keyS,GLFW_KEY_S},
//		{keyD,GLFW_KEY_D},
//		{keyF,GLFW_KEY_F},
//		{keyG,GLFW_KEY_G},
//		{keyH,GLFW_KEY_H},
//		{keyJ,GLFW_KEY_J},
//		{keyK,GLFW_KEY_K},
//		{keyL,GLFW_KEY_L},
//		{keyZ,GLFW_KEY_Z},
//		{keyX,GLFW_KEY_X},
//		{keyC,GLFW_KEY_C},
//		{keyV,GLFW_KEY_V},
//		{keyB,GLFW_KEY_B},
//		{keyN,GLFW_KEY_N},
//		{keyM, GLFW_KEY_M} 
//};
//std::queue<std::coroutine_handle<Task::promise_type>> Input::qEvents;
//std::unordered_map<std::string, std::coroutine_handle<Task::promise_type>> Input::Events;

//Input::UIs Input::UIElements;
std::list<sol::function> Input::OnClicks;

bool Input::KeyStates[71] = { false };
bool Input::KeyStatesPrev[71] = { false };

void Input::glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods)
{
	int state = glfwGetMouseButton(WindowManager::CurrentWindow->window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		OnClick();
		/*for (auto& it : Events)
		{
			it.second();
		}*/
	}
}

void Input::glfwWindowSizeCallBack(GLFWwindow* window, int width, int height)
{
	WindowManager::GetWindow("MainWindow");

	WindowManager::CurrentWindow->size.x = width;
	WindowManager::CurrentWindow->size.y = height;

	if (width > height)
	{
		RenderEngine::Renderer::ViewportOffset.x /*g_board_left_offset*/ = (width - height) / 2;
		RenderEngine::Renderer::ViewportOffset.y/*g_board_bottom_offset*/ = 0;
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
	/*g_BoardSize.x = width;
	g_BoardSize.y = height;*/

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

//Task Input::OnClick()
//{
//	auto res =  co_await Getpromise<Task::promise_type>{};
//	res->position = GetCellReal(WindowManager::GetCurrentWindow().window);
//	//auto res2 = co_await GetPromise<task::promise_type>{};
//	//int state = glfwGetMouseButton(WindowManager::CurrentWindow->window, GLFW_MOUSE_BUTTON_LEFT);
//	//if (state == GLFW_PRESS)
//	//{
//	//}
//}

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
	//OnClicks.back()();
}

//bool Input::GetKeyDown(Keys KeyCode)
//{
//	return (KeyStates[KeyCode] && !KeyStatesPrev[KeyCode]) ? true : false;
//}

//bool Input::GetKeyUp(Keys KeyCode)
//{
//	return (!KeyStates[KeyCode] && KeyStatesPrev[KeyCode]) ? true : false;
//}

//bool Input::GetKeyStay(Keys KeyCode)
//{
//	return KeyStates[KeyCode];
//}

//void Input::Update()
//{
//	for (size_t i = 0; i < 71; ++i)
//	{
//		KeyStatesPrev[i] = KeyStates[i];
//	}
//
//	for (size_t i = 0; i < 71; ++i)
//	{
//		auto key = GlEqKeys.find((Keys)i);
//
//		if(key != GlEqKeys.end()){KeyStates[i] = glfwGetKey(WindowManager::CurrentWindow->window, key->second);}
//		
//	}
//}

//glm::ivec2 Input::GetCellFromCursor(const std::string scriptName)
//{
//	std::coroutine_handle<Task::promise_type> h;
//	if (!Events.contains(scriptName))
//	{
//		auto handlerPair = Events.find(scriptName);
//
//		h = OnClick();
//		Events.emplace(scriptName, h);
//	}
//	else
//	{
//		auto handlerPair = Events.find(scriptName);
//		if ((handlerPair != Events.end()) && handlerPair->second.done())
//		{
//			glm::ivec2 buf = handlerPair->second.promise().position;
//			Events.erase(scriptName);
//			return buf;
//		}
//	}
//	return glm::ivec2(-9, -9);
//}

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