#pragma once

#include <list>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include "../Game/Figure.h"
#include "../Game/GObject.h"

class Input final
{
public:
	static void SetCallBacks(GLFWwindow* window);

	inline static Figure* selected_object;
	static void AddListener();

	//static glm::ivec2 Get_cell_pos_cursor();
private:
	static void glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods);
	static void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height);
	static void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void OnClick();

	std::list<GObject> listeners;
};