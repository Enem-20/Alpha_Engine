#pragma once

#include "../ExportPropety.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <queue>
#include <functional>

#include <glm/vec2.hpp>

class GameObject;

class IVector2Hash
{
public:
	std::size_t operator()(const glm::ivec2& c) const
	{
		return  std::hash<std::string>()(std::to_string(size_t(static_cast<size_t>(c.x) + static_cast<size_t>(c.y)) % 10000));
	}
};

class DLLEXPORT Hierarchy
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
	//static void addObj(const std::string& name);
	static void removeObject(const std::string& name);
	static std::shared_ptr<GameObject> getObject(const std::string& name);
	static GameObject& getOriginalObject(std::string name);
	static void ExecuteEvent();
	static void Clear();

	static void addGridObject(const std::string& objName);
	static void removeGridObject(const glm::ivec2& cell);
	static std::shared_ptr<GameObject> getGridObject(const glm::ivec2& cell);
	static void addPoolObject(std::shared_ptr<GameObject> obj);
	static std::shared_ptr<GameObject> getPoolObject(const std::string& name);
	static void removePoolObject(const std::string& name);
	static GameObject& addFromScriptObject(const GameObject& obj);
	static std::unordered_map<std::string, std::shared_ptr<GameObject>> GetSceneObjects();

	inline static std::unordered_map<std::string, std::shared_ptr<GameObject>> SceneObjects;
	static std::unordered_map<glm::ivec2, std::string, IVector2Hash> GridObjectsPos;
	inline static std::shared_ptr<GameObject> background;
private:
	//union AddRemove { std::function<void(const GameObject&) ; };
	inline static Hierarchy* hierarchy;
	static std::queue<std::pair<std::string, std::function<void(const std::string&)>>> qEventObjectsControl;
	static std::unordered_map<std::string, std::shared_ptr<GameObject>> uPool;
	Hierarchy() = default;
};

//std::pair<std::string, std::shared_ptr<GameObject>>