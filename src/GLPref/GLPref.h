#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"

class GLPref
{
public:
	static void glfwError(int id, const char* description);

	static int init(glm::ivec2 g_MainWindow_size);

	//static void glfwWindowSizeCallBack(GLFWwindow* window, int width, int height);

	//static void glfwKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mode);

	//static void glfwMouseCallBack(GLFWwindow* window, int button, int action, int mods);

	inline static GLFWwindow* Mainwindow;
};