#include "Hierarchy.h"

#include <iostream>

void Hierarchy::addObject(std::shared_ptr<GObject> obj)
{
	SceneObjects.emplace(obj->name, obj);
}

std::shared_ptr<GObject> Hierarchy::getObject(std::string name)
{
	auto objpair = SceneObjects.find(name);
	if (objpair != SceneObjects.end())
	{
		return objpair->second;
	}

	return nullptr;
}