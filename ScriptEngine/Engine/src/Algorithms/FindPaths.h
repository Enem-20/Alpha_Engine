#pragma once

#include <glm/vec2.hpp>

#include <queue>

#include "../Algorithms/Move.h"

class Figure;

class FindPaths
{
public:
	FindPaths() = delete;

	static std::pair<Figure*, Move*> GetMove(Figure* figure);
private:
	static int Research_cross(glm::ivec2 current);
	inline static std::queue<glm::ivec2> q;
};