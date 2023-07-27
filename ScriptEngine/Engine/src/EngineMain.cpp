

#include "EngineMain.h"
#include "GLPref/GLPref.h"

#include "UI/WindowManager.h"
#include "Resources/ResourceManager.h"
#include "Logging/Logger.h"

#include <GLFW/glfw3.h>

#include <filesystem>
#include <thread>

//#include <ppl.h>


#ifdef OGL
void EngineMain::FirstFrame()
{
	ScriptProcessor::Start();

	render();

	WindowManager::Start();

	Hierarchy::ExecuteEvent();
}

void EngineMain::ScriptUpdates()
{
	ScriptProcessor::Update();
	ScriptProcessor::FixedUpdate();
	//std::cout << "scriptFixedUpdated" << std::endl;
	ScriptProcessor::LastUpdate();
}

void EngineMain::render()
{
	auto cmp = [](const std::shared_ptr<GameObject> a, const std::shared_ptr<GameObject> b) {return (a->render_priority > b->render_priority); };
	std::priority_queue < std::shared_ptr<GameObject>, std::vector<std::shared_ptr<GameObject>>, decltype(cmp)>render_queue(cmp);
	for (auto it : Hierarchy::SceneObjects)
	{
		render_queue.push(it.second);
	}

	while (!render_queue.empty())
	{
		render_queue.top()->render();
		render_queue.pop();
	}
}

void EngineMain::Init(char** argv)
{

	
}
#endif
