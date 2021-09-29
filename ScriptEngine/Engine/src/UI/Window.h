#pragma once

#define OGL

#include <glm/vec2.hpp>

#include <memory>
#include <unordered_map>


struct GLFWwindow;
namespace UI
{
	class UIelement;
}

class Window
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
	std::shared_ptr<UI::Button>& AddUI(const UI::Button& ui);
	std::shared_ptr<UI::UIelement> GetUI(const std::string& name) const;
	void RemoveUI(const std::string name);

	GLFWwindow* window;
	glm::ivec2 size;
	std::unordered_map<std::string, std::shared_ptr<UI::UIelement>> UIs;
#endif
};