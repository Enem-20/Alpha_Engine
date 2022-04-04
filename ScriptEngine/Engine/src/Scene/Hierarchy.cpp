#include "Hierarchy.h"

#include "../GameTypes/GameObject.h"
#include "../UI/WindowManager.h"
#include "../Input/Input.h"
#include "../UI/Window.h"
#include "../Components/Transform.h"

std::queue<std::pair<std::string, std::function<void(const std::string&)>>>Hierarchy::qEventObjectsControl;
std::unordered_map<glm::ivec2, std::string, IVector2Hash> Hierarchy::GridObjectsPos;
std::unordered_map<std::string, std::shared_ptr<GameObject>> Hierarchy::uPool;

std::unordered_map<std::string, std::shared_ptr<GameObject>> Hierarchy::GetSceneObjects()
{
	return SceneObjects;
}

void Hierarchy::addObject(const GameObject& obj)
{
	std::shared_ptr<GameObject> newObj = std::make_shared<GameObject>(obj);
	SceneObjects.emplace(newObj->name, std::move(newObj));
}

GameObject& Hierarchy::addFromScriptObject(const GameObject& obj)
{
	std::shared_ptr<GameObject> newObj = std::make_shared<GameObject>(obj);
	std::string name = newObj->name;
	SceneObjects.emplace(newObj->name, std::move(newObj));
	return *getObject(std::move(name));
}

void Hierarchy::removeObjectReal(const std::string& name)
{
	auto obj = SceneObjects.find(name);
	if (obj != SceneObjects.end())
	{
		obj->second->buttons.clear();
		WindowManager::CurrentWindow->RemoveUI(name);
		auto cellObj = GridObjectsPos.find(Input::GetCell(obj->second->transform->position));
		if((cellObj != GridObjectsPos.end()) && (cellObj->second == name))
			GridObjectsPos.erase(Input::GetCell(obj->second->transform->position));
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
	GridObjectsPos.clear();
}

std::shared_ptr<GameObject> Hierarchy::getObject(const std::string& name)
{
	auto objpair = SceneObjects.find(name);
	if (objpair != SceneObjects.end())
	{
		return objpair->second;
	}

	return nullptr;
}

GameObject& Hierarchy::getOriginalObject(std::string name)
{
	auto objpair = SceneObjects.find(name);
	if (objpair != SceneObjects.end())
	{
		return *objpair->second;
	}

	//return GameObject::Null;
}

void Hierarchy::ExecuteEvent()
{
	while (!qEventObjectsControl.empty())
	{
		qEventObjectsControl.front().second(qEventObjectsControl.front().first);
		qEventObjectsControl.pop();
	}
}

void Hierarchy::addGridObject(const std::string& objName)
{
	auto obj = getObject(objName);
	glm::ivec2 cell = Input::GetCell(obj->transform->position);
	//GridObjectsPos.erase(cell);
	GridObjectsPos[cell] = objName;
}

void Hierarchy::removeGridObject(const glm::ivec2& cell)
{
	GridObjectsPos.erase(cell);
}

std::shared_ptr<GameObject> Hierarchy::getGridObject(const glm::ivec2& cell)
{
	auto obj = GridObjectsPos.find(cell);
	if(obj != GridObjectsPos.end())
		return getObject(obj->second);
	return nullptr;
}

void Hierarchy::addPoolObject(std::shared_ptr<GameObject> obj)
{
	uPool.emplace(obj->name, obj);
}

std::shared_ptr<GameObject> Hierarchy::getPoolObject(const std::string& name)
{
	auto obj_it = uPool.find(name);

	if (obj_it != uPool.end())
	{
		return obj_it->second;
	}

	return nullptr;
}

void Hierarchy::removePoolObject(const std::string& name)
{
	uPool.erase(name);
}