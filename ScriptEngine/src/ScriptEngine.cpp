#include "ScriptEngine.h"

#include "../Engine/src/Scene/Hierarchy.h"
#include "../Engine/src/Timer.h"

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