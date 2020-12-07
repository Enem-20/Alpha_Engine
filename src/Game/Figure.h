#pragma once

#include "GObject.h"
#include "AllowedCell.h"
#include <list>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"

class Figure : public GObject
{
public:
	Figure();

	void Search_path(bool BoardGraph[8][8]);

	std::list<AllowedCell> allowedCell;

	glm::vec2 cellposition;
};