#pragma once

#include <list>
#include <memory>
#include <functional>

#include<glm/vec2.hpp>

#include "../../Game/GObject.h"
#include "../Component.h"

class Figure;

class Collider final : public Component
{
public:
	Collider();

	glm::ivec2& Get_cell_size() override;
	void Set_cell_size(const glm::ivec2 new_cell_size) override;
	Figure* Get_Visitor(size_t concrete_visitor) override;
	std::list<Figure*>& Get_Visitors() override;
	void GetUpdater(std::function<void()> updater) override;
};