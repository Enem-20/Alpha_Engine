#pragma once

#include "GameObject.h"

class AllowedCell : public GameObject
{
public:
	AllowedCell(glm::vec2 Boardposition);

	void render() override;
};