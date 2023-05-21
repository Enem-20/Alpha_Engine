#pragma once

#include <sol/sol.hpp>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>

#include <unordered_map>
#include <string>

#ifndef INPUT
#define INPUT

class Input {
public:
	static void init();

	static void executeMouseCallbacks();

	static void addMouseCallback(const std::string& name, sol::function& callback);

	static void removeMouseCallback(const std::string& name);

	static glm::vec2 getNDCMousePosition();
	//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

	static std::unordered_map<std::string, sol::function&> mouseCallbacks;
};

#endif // !INPUT
