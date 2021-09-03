#pragma once

//#include <map>
//#include <string>
//#include "../GameTypes/GameTypes.h"
//#include "../Resources/Resources.h"

#include <memory>
#include <string>
#include <map>

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
	static void addObject(const std::shared_ptr<GameObject>& obj);
	static std::shared_ptr<GameObject> getObject(std::string name);
	inline static std::map<std::string, std::shared_ptr<GameObject>> SceneObjects;
	inline static std::shared_ptr<GameObject> background;
private:
	inline static Hierarchy* hierarchy;
	Hierarchy() = default;
};

//std::pair<std::string, std::shared_ptr<GameObject>>