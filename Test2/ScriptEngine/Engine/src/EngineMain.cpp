#include "EngineMain.h"
#include "GLPref/GLPref.h"
#include "Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "../../src/ScriptEngine.h"
#include "UI/WindowManager.h"
#include "Resources/ResourceManager.h"
#include "GameTypes/GameTypes.h"
#include "Input/Input.h"

#include <filesystem>
#include <fstream>
#include <thread>

namespace Engine
{
#ifdef OGL
	void EngineMain::FirstFrame()
	{
		GLPref::PollEvents();

		RenderEngine::Renderer::clear();

		ScriptEngine::ScriptProcessor::Start();

		render();

		Input::Update();

		GLPref::SwapBuffers();
	}

	void EngineMain::ScriptUpdates()
	{
		ScriptEngine::ScriptProcessor::Update();
		ScriptEngine::ScriptProcessor::FixedUpdate();
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

			ResourceManager::loadJSONScene("res/default/main.json");

			FirstFrame();


			while (!GLPref::isNeedClose())
			{
				GLPref::PollEvents();

				
				RenderEngine::Renderer::clear();

				render();
				
				std::thread th(Input::Update);
				
				ScriptUpdates();
				
				th.join();

				GLPref::SwapBuffers();
			}
		}

		std::thread th(ResourceManager::UnloadAllResources);
		glfwTerminate();
		th.join();
	}
#endif
}