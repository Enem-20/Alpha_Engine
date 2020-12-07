#pragma once

#include "GObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<glm/vec2.hpp>

#include <list>
#include<array>

class Game
{
public:
	Game();
	~Game();

	static void Update(const uint64_t delta);
	static void render();
	static void setKey(const int key, const int action);
	static bool init(const glm::ivec2& boardSize, const std::string& ExecutablePath);
	static void setBoardSize(const glm::ivec2 new_BoardSize);

	static glm::ivec2 Get_BoardSize();

	inline static std::list<GObject*> fl_GObjects;
	inline static GLFWwindow* MainWindow;
	inline static int** BoardGraph;
private:
	inline static std::array<bool, 349> keys;

	static enum class EGameState
	{
		Active,
		Pause,
	};

	EGameState ECurrentGameState;
	inline static glm::ivec2 m_BoardSize;
};