#include "EngineMain.h"
#include "GLPref/GLPref.h"
#include "Renderer/Renderer.h"
#include "Scene/Scene.h"
#include "../../src/ScriptEngine.h"

#include <filesystem>
#include <fstream>
#include <thread>

namespace Engine
{
	void EngineMain::FirstFrame()
	{
		glfwPollEvents();

		RenderEngine::Renderer::clear();

		ScriptEngine::ScriptProcessor::Start();

		for (auto Objects : Hierarchy::SceneObjects)
		{
			Objects.second->render();
		}

		glfwSwapBuffers(Game::MainWindow);
	}

	void EngineMain::Init(char** argv)
	{
		GLPref::init();
		{
			Game game;
			int width, height;
			glfwGetWindowSize(GLPref::Mainwindow, &width, &height);
			Game::init(glm::ivec2(width, height), argv[0]);

			ResourceManager::loadJSONScene("res/default/main.json");

			FirstFrame();

			while (!glfwWindowShouldClose(Game::MainWindow))
			{
				glfwPollEvents();

				RenderEngine::Renderer::clear();

				ScriptEngine::ScriptProcessor::Update();
				ScriptEngine::ScriptProcessor::FixedUpdate();
				ScriptEngine::ScriptProcessor::LastUpdate();

				for (auto Objects : Hierarchy::SceneObjects)
				{
					Objects.second->render();
				}

				glfwSwapBuffers(Game::MainWindow);
			}
		}

		
		std::thread th(ResourceManager::UnloadAllResources);
		glfwTerminate();
		th.join();
	}
}