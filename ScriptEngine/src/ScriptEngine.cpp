#include "ScriptEngine.h"
#include "ClassRegistrator.h"

#include "ComponentSystem/Collider2D.h"
#include "ComponentSystem/LuaScript.h"
#include "Renderer/src/WindowManager.h"
#include "Renderer/src/Vulkan/VulkanRenderer.h"
#include "Resources/ResourceManager.h"
#include "GameTypes/GameObject.h"
#include "Input/Input.h"
#include "Physics/Raycast.h"
#include "Renderer/src/ImGui/ImGui.h"
//#include "GLPref/GLPref.h"
#include "Tools/Timer.h"

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
	L->open_libraries(sol::lib::package, sol::lib::base, sol::lib::math);
	GeneralTimer();
	sol::table Lobject = (*L)["Engine"].get_or_create<sol::table>();
	
	std::thread th(ClassRegistrator::Registration, &Lobject);
	th.join();


}

void ScriptProcessor::Start() {
	auto gameObjects = ResourceManager::getResourcesWithType<GameObject>();
	if(gameObjects)
		for (auto gameObject : *gameObjects) {
			//auto scripts = gameObject.second.getResource<GameObject>()->getComponentsWithType<LuaScript>();
			//if (scripts)
			//	for (auto sprite : *scripts) {
			//		sprite.second.getComponentFromView<LuaScript>()->Start();
			//	}
			gameObject.second.getResource<GameObject>()->Start();
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

void ScriptProcessor::DestroyAll() {
	L->collect_garbage();
	L.reset();
	GenTimer.reset();
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
	auto L = ScriptProcessor::getL();
	ResourceManager::SetLuaState(L);

	ScriptProcessor::init({});
	ResourceManager::loadJSONGameOjects("res/saves/GameObjects");
	
	std::shared_ptr<BaseRenderer> renderer = ResourceManager::makeResource<VulkanRenderer>("main");

	Input::init();
	ImGuiManager::init();


	ScriptProcessor::Start();

	while (!renderer->windowShouldClose()) {
		renderer->render();
	}

	ResourceManager::UnloadAllResources();
	Input::freeResources();
	L.reset();
	//obj.reset();
	ScriptProcessor::DestroyAll();

	ImGuiManager::destroy();
	renderer.reset();

}