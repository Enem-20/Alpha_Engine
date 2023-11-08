#pragma once

#ifndef INPUT
#define INPUT

#include "API/ExportPropety.h"

#include <string>


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

	static void freeResources();

	static std::unordered_map<std::string, sol::function> mouseCallbacks;
};

#endif // !INPUT
