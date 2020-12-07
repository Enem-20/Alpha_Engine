#include "Algorithms/hash_table.h"

#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/vec2.hpp"

#include "Game/AllowedCell.h"
#include "Game/Desk.h"
#include "Game/Figure.h"

#include "GLPref/GLPref.h"
#include "Resources/ResourceManager.h"
#include "Game/Game.h"
#include "Game/GObject.h"
#include "Game/Desk.h"

//GLfloat points[] =
//{
//	0.0f, 50.0f, 0.0f,
//	50.0f, -50.0f, 0.0f,
//	-50.0f, -50.0f, 0.0f
//};
//
//GLfloat colors[] =
//{
//	1.0f, 0.0f, 0.0f,
//	0.0f, 1.0f, 0.0f,
//	0.0f, 0.0f, 1.0f
//};
//
//GLfloat texCoord[] =
//{
//	0.5f, 1.0f,
//	1.0f, 0.0f,
//	0.0f, 0.0f
//};

int main(int argc, char** argv)
{
	GLPref::init();
	{
		glm::ivec2 g_MainWindow_size(1080, 1080);
		glm::ivec2 g_BoardSize(g_MainWindow_size);
		Game game;
		Game::init(g_BoardSize, argv[0]);

		while (!glfwWindowShouldClose(Game::MainWindow))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			Game::render();			

			glfwSwapBuffers(Game::MainWindow);

			glfwPollEvents();
		}
	}
	ResourceManager::UnloadAllResources();
	glfwTerminate();

	return 0;
}