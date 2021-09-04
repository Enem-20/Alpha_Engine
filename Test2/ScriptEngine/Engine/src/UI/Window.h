#pragma once

#define OGL

#include <glm/vec2.hpp>

#include <memory>
#include <string>


class GLFWwindow;

class Window
{
#ifdef OGL
public:
	Window();
	~Window();
	Window(GLFWwindow*&& window);
	Window(std::string name, int width, int height);
	GLFWwindow* GetRaw();
	void SetWindow(GLFWwindow* window);
	std::shared_ptr<Window> CreateWindow(std::string name, int width, int height);
	void Update();


	GLFWwindow* window;
	glm::ivec2 size;
#endif
};