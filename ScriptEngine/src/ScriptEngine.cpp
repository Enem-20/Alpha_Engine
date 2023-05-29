#include "ScriptEngine.h"
#include "ClassRegistrator.h"

#include "ComponentSystem/src/LuaScript.h"
#include "Renderer/src/WindowManager.h"
#include "Renderer/src/Renderer.h"
#include "Resources/ResourceManager.h"
#include "GameTypes/GameObject.h"
#include "Input/src/Input.h"
#include "Renderer/src/ImGui/ImGui.h"
//#include "GLPref/GLPref.h"
#include "Timer.h"

#include <thread>
#include <queue>
#include <unordered_map>

std::shared_ptr<Timer> ScriptProcessor::GenTimer;
std::shared_ptr <sol::state> ScriptProcessor::L = std::make_shared<sol::state>();

std::shared_ptr<sol::state> ScriptProcessor::getL()
{
	return L;
}

std::shared_ptr<Timer>& ScriptProcessor::GeneralTimer()
{
	return GenTimer;
}

void ScriptProcessor::render()
{

}

void ScriptProcessor::FirstFrame()
{
	ScriptProcessor::Start();
}

void ScriptProcessor::init(char** argv)
{
	/*Instance instance;
	auto dbgMsg = DebugMessanger::getDbgMsgInstance();*/

	GeneralTimer() = std::make_shared<Timer>();
	L->open_libraries(sol::lib::base);
	GeneralTimer();
	sol::table Lobject = (*L)["Engine"].get_or_create<sol::table>();
	std::thread th(ClassRegistrator::Registration, &Lobject);
	th.join();


}

void ScriptProcessor::Start() {
	auto gameObjects = ResourceManager::getResourcesWithType<GameObject>();
	if(gameObjects)
		for (auto gameObject : *gameObjects) {
			auto scripts = gameObject.second.getResource<GameObject>()->getComponentsWithType<LuaScript>();
			if (scripts)
				for (auto sprite : *scripts) {
					sprite.second.getComponentFromView<LuaScript>()->Start();
				}
		}


}
void ScriptProcessor::Update()
{
	//for (const auto& itObjects : Hierarchy::GetSceneObjects())
	//{
	//	for (auto& itScripts : itObjects.second->GetScripts())
	//	{
	//		GeneralTimer()->StartUpdateTimer();
	//		itScripts.second->Update();
	//		GeneralTimer()->EndUpdateTimer();
	//	}
	//}
}
void ScriptProcessor::FixedUpdate()
{
	//for (const auto& itObjects : Hierarchy::GetSceneObjects())
	//{
	//	for (auto& itScripts : itObjects.second->GetScripts())
	//	{
	//		itScripts.second->FixedUpdate();
	//	}
	//}
}
void ScriptProcessor::LastUpdate()
{
	//for (const auto& itObjects : Hierarchy::GetSceneObjects())
	//{
	//	for (auto& itScripts : itObjects.second->GetScripts())
	//	{
	//		itScripts.second->LastUpdate();
	//	}
	//}
}

void ScriptProcessor::ScriptUpdates()
{
	ScriptProcessor::Update();
	ScriptProcessor::FixedUpdate();
	//std::cout << "scriptFixedUpdated" << std::endl;
	ScriptProcessor::LastUpdate();
}


void main(int argc, char** argv) {


	ResourceManager::SetExecutablePath(argv[0]);
	ResourceManager::SetLuaState(ScriptProcessor::getL());

	ScriptProcessor::init({});
	ResourceManager::loadJSONGameOjects("res/saves/GameObjects");

	ScriptProcessor::Start();
	auto obj = ResourceManager::getResource<GameObject>("Another");
	std::shared_ptr<Renderer> renderer = ResourceManager::makeResource<Renderer>("main");

	Input::init();
	ImGuiManager::init();

	renderer/*.lock()*/->render();
	ScriptProcessor::getL()->collect_garbage();

	ResourceManager::UnloadAllResources();
	obj.reset();

	ImGuiManager::destroy();
	renderer.reset();

}