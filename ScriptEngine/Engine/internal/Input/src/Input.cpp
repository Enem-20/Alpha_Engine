#include "Input.h"

#include "../../Physics/src/Raycast.h"
#include "../../ComponentSystem/src/Collider2D.h"
#include "../../Renderer/src/WindowManager.h"
#include "../../Renderer/src/Window.h"

#include "../../src/Helpers/casts.h"

#include <iostream>

std::unordered_map<std::string, sol::function&> Input::mouseCallbacks;


void /*Input::*/mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		Input::executeMouseCallbacks();
		auto mouseNDCPosition = Input::getNDCMousePosition();
		std::cout << "position: (" << mouseNDCPosition.x << ',' << mouseNDCPosition.y << ')' << '\n';
		Raycast ray;
		auto collider = ray.closestBodyHit(glm::vec3(mouseNDCPosition, 0.0f), glm::vec3(mouseNDCPosition, 100.0f));
		if(collider)
			std::cout << "Collider name: " << collider->name << '\n';
	}
		
}


void Input::init() {
	glfwSetMouseButtonCallback(WindowManager::CurrentWindow->GetRaw(), mouse_button_callback);
}

void Input::executeMouseCallbacks() {
	for (auto& callback : mouseCallbacks)
		callback.second();
}

void Input::addMouseCallback(const std::string& name, sol::function& callback) {
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

	return glm::vec2(Casts::castFromFramebufferToNDCrange(x/(float)width), Casts::castFromFramebufferToNDCrange(y/(float)height));
}
