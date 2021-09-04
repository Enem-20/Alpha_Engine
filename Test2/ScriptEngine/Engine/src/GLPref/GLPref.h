#pragma once

class GLPref
{
public:
	static void glfwError(int id, const char* description);
	static void SwapBuffers();
	static void PollEvents();
	static bool isNeedClose();

	static int init();
};