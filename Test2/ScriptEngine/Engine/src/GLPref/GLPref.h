#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"

class GLPref
{
public:
	static void glfwError(int id, const char* description);

	static int init();

	inline static GLFWwindow* Mainwindow;
};