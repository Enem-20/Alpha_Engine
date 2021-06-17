#pragma once

#include <unordered_map>
#include <memory>

#include "Window.h"

class WindowManager
{
public:
	static void init();
	static std::shared_ptr<Window> GetWindow(std::string name);
	static void AddWindow(std::string name, int width = 1080, int height = 1080);
	static std::shared_ptr<Window> CurrentWindow;
private:
	static std::unordered_map<std::string, std::shared_ptr<Window>> windows;
};