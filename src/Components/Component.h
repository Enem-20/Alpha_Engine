#pragma once

#include <memory>
#include <string>
#include <list>
#include <functional>

#include <glm/vec2.hpp>

#include "../Game/Figure.h"

#define CLASS_DECLARATION { public: Component() : componentIdentificator(std::hash<std::string>(className))}

class Component
{
public:
	Component(Figure* gObject = nullptr);

public:
	virtual void Set_cell_size(const glm::ivec2 new_cell_size) = 0;
	virtual glm::ivec2& Get_cell_size() = 0;
	virtual Figure* Get_Visitor(size_t concrete_visitor) = 0;
	virtual std::list<Figure*>& Get_Visitors() = 0;
	
	virtual void GetUpdater(std::function<void()> updater) = 0;
	Figure* gObject;
	std::hash<std::string> componentIdentificator;
	std::string className;
protected:
	std::list<Figure*> visitors;
	std::function<void()> update;
	glm::ivec2 cell_size;
};