#pragma once

#define OGL

#include "../ExportPropety.h"

#include <glm/vec2.hpp>

#include <memory>
#include <unordered_map>


struct GLFWwindow;

class UIelement;
class Button;


class DLLEXPORT Window
{
#ifdef OGL
public:
	Window();
	~Window();
	Window(GLFWwindow* window);
	Window(std::string name, int width, int height);
	GLFWwindow* GetRaw();
	void SetWindow(GLFWwindow* window);
	std::shared_ptr<Window> CreateWindow(const std::string& name, const unsigned int& width, const unsigned int& height);
	void Awake();
	void Start();
	void Update();
	void FixedUpdate();
	std::shared_ptr<Button>& AddUI(const Button& ui);
	std::shared_ptr<UIelement> GetUI(const std::string& name) const;
	void RemoveUI(const std::string name);

	GLFWwindow* window;
	glm::ivec2 size;
	std::unordered_map<std::string, std::shared_ptr<UIelement>> UIs;
#endif
};