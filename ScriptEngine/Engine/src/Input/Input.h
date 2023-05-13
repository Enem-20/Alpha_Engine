#pragma once

#include "../ExportPropety.h"

//#define OGL

#include <list>

#include <sol/sol.hpp>
#include "glm/vec2.hpp"

struct GLFWwindow;
//ruler or commander
class DLLEXPORT Input
{
#ifdef OGL
public:
	static void Update();

	static void SetCallBacks(GLFWwindow* window);
	static void glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods);
	static void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height);
	static void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);

	static void OnClick();

	static glm::ivec2 GetCellReal();
	static glm::ivec2 GetCell(const glm::vec2& objPos);
	static std::list<sol::function> OnClicks;
	static void AddListener(const sol::function& func);

#endif
};