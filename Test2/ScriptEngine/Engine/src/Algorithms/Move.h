#pragma once

#include <glm/vec2.hpp>

class Move
{
public:
	Move(glm::ivec2 coordinate, int value = 0)
	{
		this->coordinate = coordinate;
		this->value = value;
	}

	int value;
	glm::ivec2 coordinate;
};

