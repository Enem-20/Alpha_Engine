#pragma once

#include <map>
#include <string>
#include "../Game/GObject.h"

class Hierarchy
{
	friend class SceneManager;
public:
	static Hierarchy* GetInstanceHierarchy()
	{
		if (!hierarchy)
		{
			return hierarchy = new Hierarchy;
		}

		return hierarchy;
	}
	static void addObject(std::shared_ptr<GObject> obj);
	static std::shared_ptr<GObject> getObject(std::string name);
	inline static std::map<std::string, std::shared_ptr<GObject>> SceneObjects;
	
private:
	static Hierarchy* hierarchy;
	Hierarchy() = default;
	
};