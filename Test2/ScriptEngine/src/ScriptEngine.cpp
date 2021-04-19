#include "ScriptEngine.h"
#include "../Engine/src/Scene/Hierarchy.h"
#include "../Engine/src/GameTypes/GameObject.h"


struct callStart final
{
	void operator()(Components::LuaScript& l) { l.Start(); }
};
struct callUpdate final
{
	void operator()(Components::LuaScript& l) { l.Update(); }
};
struct callFixedUpdate final
{
	void operator()(Components::LuaScript& l) { l.FixedUpdate(); }
};
struct callLastUpdate final
{
	void operator()(Components::LuaScript& l) { l.LastUpdate(); }
};

namespace ScriptEngine
{
	void ScriptProcessor::init()
	{
		GeneralTimer = std::make_shared<Timer>();
		L.open_libraries(sol::lib::base);
	}

	void ScriptProcessor::Start()
	{
		for (const auto& itObjects : Hierarchy::SceneObjects)
		{
			for (auto& itComponents : itObjects.second->m_Components)
			{
				std::visit(callStart{}, itComponents.second);
			}
		}
	}
	void ScriptProcessor::Update()
	{
		for (const auto& itObjects : Hierarchy::SceneObjects)
		{
			for (auto& itComponents : itObjects.second->m_Components)
			{
				GeneralTimer->StartUpdateTimer();
				std::visit(callUpdate{}, itComponents.second);
				GeneralTimer->EndUpdateTimer();
			}
		}
	}
	void ScriptProcessor::FixedUpdate()
	{
		for (const auto& itObjects : Hierarchy::SceneObjects)
		{
			for (auto& itComponents : itObjects.second->m_Components)
			{
				std::visit(callFixedUpdate{}, itComponents.second);
			}
		}
	}
	void ScriptProcessor::LastUpdate()
	{
		for (const auto& itObjects : Hierarchy::SceneObjects)
		{
			for (auto& itComponents : itObjects.second->m_Components)
			{
				std::visit(callLastUpdate{}, itComponents.second);
			}
		}
	}
}