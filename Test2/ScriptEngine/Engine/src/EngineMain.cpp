#include "GameTypes/GameTypes.pch"
#include "EngineMain.h"
#include "GLPref/GLPref.h"
#include "Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "../../src/ScriptEngine.h"
#include "UI/WindowManager.h"
#include "Resources/ResourceManager.h"

#include "Input/Input.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <filesystem>
#include <fstream>
#include <thread>
#include <chrono>

//#include <ppl.h>

namespace Engine
{
#ifdef OGL
	void EngineMain::FirstFrame()
	{
		//GLPref::PollEvents();

		//ResourceManager::loadJSONText("");

		//RenderEngine::Renderer::clear();

		ScriptEngine::ScriptProcessor::Start();

		render();

		Input::Update();

		WindowManager::Update();
		

		//GLPref::SwapBuffers();
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

			ResourceManager::loadJSONScene("res/default/main.json");
			size_t countFrames = 0;
			FirstFrame();
			++countFrames;
			
			while (!GLPref::isNeedClose())
			{
#ifndef NDEBUG
				//auto start = std::chrono::high_resolution_clock::now();
#endif
				//GLPref::PollEvents();
				glfwPollEvents();
				glClear(GL_COLOR_BUFFER_BIT);
				//RenderEngine::Renderer::clear();

				
				
				std::thread th(Input::Update);
				
				ScriptUpdates();

				render();

				th.join();

				

				WindowManager::Update();
				
				//GLPref::SwapBuffers();
#ifndef NDEBUG
				//auto end = std::chrono::high_resolution_clock::now();

				//std::cout << std::chrono::duration<float>(end-start).count() << std::endl;
#endif

				++countFrames;
				if(countFrames > 1000)
					break;
			}
		}

		std::thread th(ResourceManager::UnloadAllResources);
		glfwTerminate();
		th.join();
	}
#endif
}