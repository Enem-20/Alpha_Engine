#pragma once

#include "GObject.h"

class AllowedCell : public GObject
{
public:
	AllowedCell(glm::vec2 Boardposition);

	void render() override;
};