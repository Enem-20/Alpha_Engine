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
	static void removeObject(const std::string& name);
	static std::shared_ptr<GameObject> getObject(std::string name);
	static void ExecuteEvent();

	inline static std::unordered_map<std::string, std::shared_ptr<GameObject>> SceneObjects;
	inline static std::shared_ptr<GameObject> background;
private:
	//union AddRemove { std::function<void(const GameObject&) ; };
	inline static Hierarchy* hierarchy;
	static std::queue<std::pair<std::string, std::function<void(const std::string&)>>> qEventObjectsControl;
	Hierarchy() = default;
};

//std::pair<std::string, std::shared_ptr<GameObject>>