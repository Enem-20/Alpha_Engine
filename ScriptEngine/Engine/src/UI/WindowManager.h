#pragma once

#include "../ExportPropety.h"

#include <unordered_map>
#include <memory>

class Window;

class DLLEXPORT WindowManager
{
public:
	static int init(std::string name, int width = 1080, int height = 1080);
	static void ShutDown();

	static std::shared_ptr<Window> GetWindow(std::string name);
	static std::shared_ptr<Window> AddWindow(std::string name, int width = 1080, int height = 1080);
	static Window& GetCurrentWindow();
	static std::shared_ptr<Window> CurrentWindow;
	static void Start();
	static void Update();
private:
	static std::unordered_map<std::string, std::shared_ptr<Window>> windows;
};