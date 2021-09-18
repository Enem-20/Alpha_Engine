#pragma once

#define OGL

#include "../GameTypes/GameTypes.pch"

#include <list>
#include <memory>
#include <map>
#include <functional>
//#include <coroutine>
//#include <future>

#include <sol/sol.hpp>
#include "glm/vec2.hpp"

struct GLFWwindow;

template<typename PromiseType>
struct Getpromise
{
	PromiseType* p_;
	bool await_ready() const noexcept { return false; }
	void await_suspend(std::coroutine_handle<PromiseType> h)
	{
		
		p_ = &h.promise();
	}
	PromiseType* await_resume() const noexcept { return p_; }
};

struct Task {
	struct promise_type {
		glm::vec2 position;
		
		Task get_return_object() 
		{ return Task{ .h_ = std::coroutine_handle<promise_type>::from_promise(*this) }; }
		std::suspend_never initial_suspend() 
		{
			return {};
		}
		std::suspend_never final_suspend() noexcept { return {}; }
		void return_void() {}
		void unhandled_exception() {}
	};
	std::coroutine_handle<promise_type> h_;
	operator std::coroutine_handle<promise_type>() const { return h_; }
};

class Input
{
public:
	static enum Keys
	{
		key0,
		key1,
		key2,
		key3,
		key4,
		key5,
		key6,
		key7,
		key8,
		key9,
		keyN0,
		keyM1,
		keyN2,
		keyN3,
		keyN4,
		keyN5,
		keyN6,
		keyN7,
		keyN8,
		keyN9,
		keyF1,
		keyF2,
		keyF3,
		keyF4,
		keyF5,
		keyF6,
		keyF7,
		keyF8,
		keyF9,
		keyF10,
		keyF11,
		keyF12,
		keyTab,
		keyCaps,
		keyLShift,
		keyRShift,
		keyLCtrl,
		keyRCtrl,
		keyLAlt,
		keyRAlt,
		keyEnter,
		keyBackSpace,
		keyLeftArrow,
		keyUpArrow,
		keyRightArrow,
		keyDownArrow,
		keyQ,
		keyW,
		keyE,
		keyR,
		keyT,
		keyY,
		keyU,
		keyI,
		keyO,
		keyP,
		keyA,
		keyS,
		keyD,
		keyF,
		keyG,
		keyH,
		keyJ,
		keyK,
		keyL,
		keyZ,
		keyX,
		keyC,
		keyV,
		keyB,
		keyN,
		keyM
	};
	static bool KeyStates[71];
	static bool KeyStatesPrev[71];

	static bool GetKeyDown(Keys KeyCode);
	static bool GetKeyUp(Keys KeyCode);
	static bool GetKeyStay(Keys KeyCode);

	//static void AddUI(std::string name, std::shared_ptr<UI::UIelement> UIElement);
	//static std::shared_ptr<UI::UIelement> GetUI(std::string name);
private:	
	//static std::map<std::string, std::shared_ptr<UI::UIelement>> UIElements;
	//typedef std::map<std::string, std::shared_ptr<UI::UIelement>> UIs;
#ifdef OGL
public:
	static void Update();

	static void SetCallBacks(GLFWwindow* window);
	static void glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods);
	static void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height);
	static void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
	//static Task OnClick();
	static void OnClick();
	//static glm::ivec2 GetCellFromCursor();
	static glm::ivec2 GetCellReal();
	static glm::ivec2 GetCell(glm::vec2 objPos);
	static std::list<sol::protected_function> OnClicks;
	static void AddListener(const sol::protected_function& func);
	//static std::unordered_map<std::string, std::coroutine_handle<Task::promise_type>> Events;
	//static std::shared_ptr<UI::UIelement> CheckShotUI(const glm::dvec2& mousePos);
private:
	//static std::map<Keys, int> GlEqKeys;
#endif
	
	//static std::queue<std::coroutine_handle<Task::promise_type>> qEvents;
};