#pragma once

//#include <map>
//#include <string>
//#include "../GameTypes/GameTypes.h"
//#include "../Resources/Resources.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>

class GameObject;

class IVector2Hash
{
public:
	std::size_t operator()(const glm::ivec2& c) const
	{
		return  std::hash<std::string>()(std::to_string(size_t(c.x + c.y) % 10000));
	}
};

class Hierarchy
{
	//friend class SceneManager;
public:
	static Hierarchy* GetInstanceHierarchy()
	{
		if (!hierarchy)
		{
			return hierarchy = new Hierarchy;
		}

		return hierarchy;
	}
	static void removeObjectReal(const std::string& name);
	static void addObject(const GameObject& obj);
	static void addObj(const std::string& name);
	static void removeObject(const std::string& name);
	static std::shared_ptr<GameObject> getObject(std::string name);
	static void ExecuteEvent();
	static void Clear();

	static void addGridObject(const GameObject& obj);
	static void removeGridObject(const glm::ivec2& cell);
	static std::shared_ptr<GameObject> getGridObject(const glm::ivec2& cell);

	inline static std::unordered_map<std::string, std::shared_ptr<GameObject>> SceneObjects;
	static std::unordered_map<glm::ivec2, std::shared_ptr<GameObject>, IVector2Hash> GridObjectsPos;
	inline static std::shared_ptr<GameObject> background;
private:
	//union AddRemove { std::function<void(const GameObject&) ; };
	inline static Hierarchy* hierarchy;
	static std::queue<std::pair<std::string, std::function<void(const std::string&)>>> qEventObjectsControl;
	Hierarchy() = default;
};

//std::pair<std::string, std::shared_ptr<GameObject>>