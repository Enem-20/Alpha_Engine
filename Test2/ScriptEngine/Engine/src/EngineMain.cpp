#include "EngineMain.h"
#include "GLPref/GLPref.h"
#include "Renderer/Renderer.h"


namespace Engine
{
	void EngineMain::Init(char** argv)
	{
		GLPref::init();
		{
			Game game;
			int width, height;
			glfwGetWindowSize(GLPref::Mainwindow, &width, &height);
			Game::init(glm::ivec2(width, height), argv[0]);

			Game::desk = new Desk;
			Game::desk->SetSprite("sprite_Desk", "Desk", "SpriteShader", Game::m_BoardSize.x, Game::m_BoardSize.y, "");

			int it_Figures_black = 0;
			int it_Figures_white = 0;

			for (int i = 0; i < 8; ++i)
			{
				for (int j = 0; j < 8; ++j)
				{
					if (Game::BoardGraph[i][j] == 1)
					{
						Game::figures_white[glm::ivec2(i, j)] = new Figure;
						Game::figures_white[glm::ivec2(i, j)]->SetSprite("Figure_white", "Figures", "SpriteShader", 135, 135, "white_pawn");
						Game::figures_white[glm::ivec2(i, j)]->fraction = 1;

						Game::figures_white[glm::ivec2(i, j)]->Translate(glm::vec3(i, j, 0));
						Game::figures_white[glm::ivec2(i, j)]->cellposition = glm::vec2(i, j);
						Game::white_home[it_Figures_white] = glm::ivec2(i, j);
						++it_Figures_white;
					}
					else if (Game::BoardGraph[i][j] == 2)
					{
						Game::figures_black[glm::ivec2(i, j)] = new Figure;
						Game::figures_black[glm::ivec2(i, j)]->SetSprite("Figure_black", "Figures", "SpriteShader", 135, 135, "black_pawn");
						Game::figures_black[glm::ivec2(i, j)]->fraction = 2;

						Game::figures_black[glm::ivec2(i, j)]->Translate(glm::vec3(i, j, 0));
						Game::figures_black[glm::ivec2(i, j)]->cellposition = glm::vec2(i, j);
						++it_Figures_black;
					}
				}
			}
			//Game::ai.CollectMoves(StandartDebut);
			while (!glfwWindowShouldClose(Game::MainWindow))
			{
				glfwPollEvents();

				RenderEngine::Renderer::clear();

				Game::desk->render();
				for (auto it_black : Game::figures_black)
				{
					it_black.second->render();
				}
				for (auto it_white : Game::figures_white)
				{
					it_white.second->render();
				}

				glfwSwapBuffers(Game::MainWindow);
			}
		}
		ResourceManager::UnloadAllResources();
		glfwTerminate();
	}
}