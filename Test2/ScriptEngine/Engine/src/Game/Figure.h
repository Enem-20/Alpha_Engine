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
	
	void render() override;
	//void update() override;

	void Search_path(glm::ivec2 start, int fraction);

	std::list<AllowedCell*> allowedCell;

	int fraction;
};