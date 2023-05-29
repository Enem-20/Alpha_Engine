#pragma once

#ifndef INPUT
#define INPUT

#include "../../src/ExportPropety.h"

#ifdef SHOWONBUILD

#include <glfw/glfw3.h>


#include <string>
#else
//namespace glm {
//	struct vec2;
//}

//namespace sol {
//	class function;
//}
#endif

#include <sol/sol.hpp>
#include <glm/glm.hpp>

#include <unordered_map>



class DLLEXPORT Input {
public:
	static void init();

	static void executeMouseCallbacks();

	static void addMouseCallback(const std::string& name, const sol::function& callback);

	static void removeMouseCallback(const std::string& name);

	static glm::vec2 getNDCMousePosition();
	//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#ifdef SHOWONBUILD
	static std::unordered_map<std::string, sol::function> mouseCallbacks;
#endif
};

#endif // !INPUT
