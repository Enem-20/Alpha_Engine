#include "GameTypes/GameTypes.pch"
#include "EngineMain.h"
#include "GLPref/GLPref.h"

#include "../../src/ScriptEngine.h"
#include "UI/WindowManager.h"
#include "Resources/ResourceManager.h"

#include <GLFW/glfw3.h>

#include <filesystem>
#include <thread>

//#include <ppl.h>

namespace Engine
{
#ifdef OGL
	void EngineMain::FirstFrame()
	{
		ScriptEngine::ScriptProcessor::Start();

		render();

		WindowManager::Start();
		
		Hierarchy::ExecuteEvent();
	}

	void EngineMain::ScriptUpdates()
	{
		ScriptEngine::ScriptProcessor::Update();
		ScriptEngine::ScriptProcessor::FixedUpdate();
		//std::cout << "scriptFixedUpdated" << std::endl;
		ScriptEngine::ScriptProcessor::LastUpdate();
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

		GLPref::init();
		{
			ResourceManager::SetExecutablePath(argv[0]);
			ScriptEngine::ScriptProcessor::L.require_file("dequeue", ResourceManager::GetPath() + "/res/components/scripts/dequeue.lua");
			ResourceManager::loadJSONScene("res/default/main.json");
			size_t countFrames = 0;
			FirstFrame();
			++countFrames;
			
			while (!GLPref::isNeedClose())
			{
#ifndef NDEBUG
				//auto start = std::chrono::high_resolution_clock::now();
#endif
				glfwPollEvents();
				glClear(GL_COLOR_BUFFER_BIT);

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
		std::thread th(ResourceManager::UnloadAllResources);
		WindowManager::ShutDown();
		glfwTerminate();
		th.join();
	}
#endif
}