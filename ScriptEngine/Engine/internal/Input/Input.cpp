#include "Input.h"

#include "Physics/Raycast.h"
#include "ComponentSystem/Collider2D.h"
#include "Renderer/src/WindowManager.h"
#include "Renderer/src/Window.h"

#include "Tools/casts.h"

#include <glfw/glfw3.h>

#include <iostream>

#ifdef SHOWONBUILD
std::unordered_map<std::string, sol::function> Input::mouseCallbacks;
#endif


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		Input::executeMouseCallbacks();
	}
		
}


void Input::init() {
	glfwSetMouseButtonCallback(WindowManager::CurrentWindow->GetRaw(), mouse_button_callback);
}

void Input::executeMouseCallbacks() {
	for (auto& callback : mouseCallbacks)
		callback.second();
}

void Input::addMouseCallback(const std::string& name, const sol::function& callback) {
	mouseCallbacks.emplace(name, callback);
}

void Input::removeMouseCallback(const std::string& name) {
	if(mouseCallbacks.contains(name))
		mouseCallbacks.erase(name);
}

glm::vec2 Input::getNDCMousePosition() {
	double x = 0, y = 0;
	glfwGetCursorPos(WindowManager::CurrentWindow->GetRaw(), &x, &y);
	int width = 0, height = 0;
	glfwGetWindowSize(WindowManager::CurrentWindow->GetRaw(), &width, &height);

	return glm::vec2(Casts::castFromFramebufferToNDCrange(x/(float)width), -1 * Casts::castFromFramebufferToNDCrange(y/(float)height));
}

void Input::freeResources() {
	mouseCallbacks.clear();
}