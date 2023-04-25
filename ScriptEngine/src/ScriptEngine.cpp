#include "ScriptEngine.h"
#include "ClassRegistrator.h"

#include "../Engine/internal/Renderer/src/Vulkan/Instance.h"
#include "../Engine/internal/Renderer/src/Vulkan/DebugMessenger.h"

#include "Components/LuaScript.h"
#include "Scene/Hierarchy.h"
#include "UI/WindowManager.h"
#include "Resources/ResourceManager.h"
#include "GameTypes/GameObject.h"
#include "GLPref/GLPref.h"
#include "Timer.h"

#include <thread>
#include <queue>

std::shared_ptr<Timer> ScriptProcessor::GenTimer;
std::shared_ptr <sol::state> ScriptProcessor::L = std::make_shared<sol::state>();

sol::state& ScriptProcessor::getL()
{
	return *L;
}

std::shared_ptr<Timer>& ScriptProcessor::GeneralTimer()
{
	return GenTimer;
}

void ScriptProcessor::render()
{
	auto cmp = [](const std::shared_ptr<GameObject> a, const std::shared_ptr<GameObject> b) {return (a->GetRenderPriority() > b->GetRenderPriority()); };
	std::priority_queue < std::shared_ptr<GameObject>, std::vector<std::shared_ptr<GameObject>>, decltype(cmp)>render_queue(cmp);
	for (auto it : Hierarchy::GetSceneObjects())
	{
		render_queue.push(it.second);
	}

	while (!render_queue.empty())
	{
		render_queue.top()->render();
		render_queue.pop();
	}
}

void ScriptProcessor::FirstFrame()
{
	ScriptProcessor::Start();

	render();

	WindowManager::Start();

	Hierarchy::ExecuteEvent();
}

void ScriptProcessor::init(char** argv)
{
	Instance instance;
	auto dbgMsg = DebugMessanger::getDbgMsgInstance();

	GeneralTimer() = std::make_shared<Timer>();
	L->open_libraries(sol::lib::base);
	GeneralTimer();
	sol::table Lobject = (*L)["Engine"].get_or_create<sol::table>();
	std::thread th(ClassRegistrator::Registration, &Lobject);
	th.join();
	GLPref::init();
	{
		ResourceManager::SetExecutablePath(argv[0]);
		ResourceManager::SetLuaState(L);
		/*ScriptProcessor::getL().require_file("dequeue", ResourceManager::GetPath() + "/res/components/scripts/dequeue.lua");*/
		ResourceManager::loadJSONScene("res/default/main.json");
		size_t countFrames = 0;
		FirstFrame();
		++countFrames;

		while (!GLPref::isNeedClose())
		{
#ifndef NDEBUG
			//auto start = std::chrono::high_resolution_clock::now();
#endif
			GLPref::PollEvents();
			GLPref::ClearScreenWithBufferColor();

			ResourceManager::loadExecute();


			ScriptUpdates();

			render();

			WindowManager::Update();

			Hierarchy::ExecuteEvent();
#ifndef NDEBUG
			//auto end = std::chrono::high_resolution_clock::now();

			//std::cout << std::chrono::duration<float>(end-start).count() << std::endl;
#endif

		}
	}
	std::thread th1(ResourceManager::UnloadAllResources);
	WindowManager::ShutDown();

	th1.join();
}

void ScriptProcessor::Start()
{
	for (const auto& itObjects : Hierarchy::GetSceneObjects())
	{
		for (auto& itScripts : itObjects.second->GetScripts())
		{
			itScripts.second->Start();
		}
	}
}
void ScriptProcessor::Update()
{
	for (const auto& itObjects : Hierarchy::GetSceneObjects())
	{
		for (auto& itScripts : itObjects.second->GetScripts())
		{
			GeneralTimer()->StartUpdateTimer();
			itScripts.second->Update();
			GeneralTimer()->EndUpdateTimer();
		}
	}
}
void ScriptProcessor::FixedUpdate()
{
	for (const auto& itObjects : Hierarchy::GetSceneObjects())
	{
		for (auto& itScripts : itObjects.second->GetScripts())
		{
			itScripts.second->FixedUpdate();
		}
	}
}
void ScriptProcessor::LastUpdate()
{
	for (const auto& itObjects : Hierarchy::GetSceneObjects())
	{
		for (auto& itScripts : itObjects.second->GetScripts())
		{
			itScripts.second->LastUpdate();
		}
	}
}

void ScriptProcessor::ScriptUpdates()
{
	ScriptProcessor::Update();
	ScriptProcessor::FixedUpdate();
	//std::cout << "scriptFixedUpdated" << std::endl;
	ScriptProcessor::LastUpdate();
}
