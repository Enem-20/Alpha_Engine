#include "Hierarchy.h"

#include "../GameTypes/GameTypes.pch"
#include "../Resources/Resources.pch"

std::queue<std::pair<std::string, std::function<void(const std::string&)>>>Hierarchy::qEventObjectsControl;
std::unordered_map<glm::ivec2, std::shared_ptr<GameObject>, IVector2Hash> Hierarchy::GridObjectsPos;

void Hierarchy::addObject(const GameObject& obj)
{
	//std::pair<std::string, std::shared_ptr<GameObject>>* _pair = new std::pair<std::string, std::shared_ptr<GameObject>>(obj->name, obj);
	SceneObjects.emplace(obj.name, std::make_shared<GameObject>(obj));
}

void Hierarchy::removeObjectReal(const std::string& name)
{
	auto obj = SceneObjects.find(name);
	if (obj != SceneObjects.end())
	{
		obj->second->buttons.clear();
		WindowManager::CurrentWindow->RemoveUI(name);
		SceneObjects.erase(name);
	}
}

void Hierarchy::removeObject(const std::string& name)
{
	qEventObjectsControl.push({name, removeObjectReal});
}

void Hierarchy::Clear()
{
	for (auto& it : SceneObjects)
	{
		it.second->buttons.clear();
		WindowManager::CurrentWindow->RemoveUI(it.second->name);
	}
	SceneObjects.clear();
}

std::shared_ptr<GameObject> Hierarchy::getObject(std::string name)
{
	auto objpair = SceneObjects.find(name);
	if (objpair != SceneObjects.end())
	{
		return objpair->second;
	}
}

void Hierarchy::ExecuteEvent()
{
	while (!qEventObjectsControl.empty())
	{
		qEventObjectsControl.front().second(qEventObjectsControl.front().first);
		qEventObjectsControl.pop();
	}
}

void Hierarchy::addGridObject(const GameObject& obj)
{
	GridObjectsPos.emplace(Input::GetCell(obj.transform->position), std::make_shared<GameObject>(obj));
}

void Hierarchy::removeGridObject(const glm::ivec2& cell)
{
	GridObjectsPos.erase(cell);
}

std::shared_ptr<GameObject> Hierarchy::getGridObject(const glm::ivec2& cell)
{
	auto obj = GridObjectsPos.find(cell);
	if (obj != GridObjectsPos.end())
	{
		return obj->second;
	}

	return nullptr;
}