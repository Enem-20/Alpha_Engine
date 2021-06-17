#include "ScriptEngine.h"
#include "../Engine/src/Scene/Hierarchy.h"
#include "../Engine/src/GameTypes/GameObject.h"


//struct callStart final
//{
//	void operator()(Components::LuaScript& l) { l.Start(); }
//	void operator()(UI::Button& button) {}
//	void operator()(RenderEngine::Sprite& sprite){}
//};
//struct callUpdate final
//{
//	void operator()(Components::LuaScript& l) { l.Update(); }
//	void operator()(UI::Button& button){}
//	void operator()(RenderEngine::Sprite& sprite) {}
//};
//struct callFixedUpdate final
//{
//	void operator()(Components::LuaScript& l) { l.FixedUpdate(); }
//	void operator()(UI::Button& button) {}
//	void operator()(RenderEngine::Sprite& sprite) {}
//};
//struct callLastUpdate final
//{
//	void operator()(Components::LuaScript& l) { l.LastUpdate(); }
//	void operator()(UI::Button& button) {}
//	void operator()(RenderEngine::Sprite& sprite) {}
//};

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
			for (auto& itScripts : itObjects.second->scripts)
			{
				itScripts.second->Start();
			}
		}
	}
	void ScriptProcessor::Update()
	{
		for (const auto& itObjects : Hierarchy::SceneObjects)
		{
			for (auto& itScripts : itObjects.second->scripts)
			{
				GeneralTimer->StartUpdateTimer();
				itScripts.second->Update();
				GeneralTimer->EndUpdateTimer();
			}
		}
	}
	void ScriptProcessor::FixedUpdate()
	{
		for (const auto& itObjects : Hierarchy::SceneObjects)
		{
			for (auto& itScripts : itObjects.second->scripts)
			{
				itScripts.second->FixedUpdate();
			}
		}
	}
	void ScriptProcessor::LastUpdate()
	{
		for (const auto& itObjects : Hierarchy::SceneObjects)
		{
			for (auto& itScripts : itObjects.second->scripts)
			{
				itScripts.second->LastUpdate();
			}
		}
	}
}