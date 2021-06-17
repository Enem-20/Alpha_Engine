#include "Hierarchy.h"

#include "../GameTypes/GameTypes.h"
#include "../Resources/Resources.h"

void Hierarchy::addObject(std::shared_ptr<GameObject>& obj)
{
	std::pair<std::string, std::shared_ptr<GameObject>>* _pair = new std::pair<std::string, std::shared_ptr<GameObject>>(obj->name, obj);
	SceneObjects.emplace(*_pair);
}

std::shared_ptr<GameObject> Hierarchy::getObject(std::string name)
{
	auto objpair = SceneObjects.find(name);
	if (objpair != SceneObjects.end())
	{
		return objpair->second;
	}

	return nullptr;
}