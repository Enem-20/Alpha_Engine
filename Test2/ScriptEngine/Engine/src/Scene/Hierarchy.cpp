#include "Hierarchy.h"

#include "../GameTypes/GameTypes.pch"
#include "../Resources/Resources.pch"

std::queue<std::pair<std::string, std::function<void(const std::string&)>>>Hierarchy::qEventObjectsControl;

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