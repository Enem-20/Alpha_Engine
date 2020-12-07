#include "../GLPref/GLPref.h"
#include "Game.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include<glm/vec2.hpp>
#include<glm/mat4x4.hpp>

#include "Desk.h"
#include "AllowedCell.h"
#include "Figure.h"

#include <iostream>

Game::Game()
	: ECurrentGameState(EGameState::Active)
{
	//0 - free slot, 1 - white figure, 2 - black figure
	int BoardGraph[8][8] =
	{
	2,2,2,0,0,0,0,0,
	2,2,2,0,0,0,0,0,
	2,2,2,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,1,
	0,0,0,0,0,1,1,1,
	0,0,0,0,0,1,1,1
	};

	this->BoardGraph = new int* [8];
	for (int i = 0; i < 8; ++i)
	{
		this->BoardGraph[i] = new int[8];
	}


	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			this->BoardGraph[i][j] = BoardGraph[i][j];
		}
	}
	keys.fill(false);

	MainWindow = GLPref::Mainwindow;
}
Game::~Game()
{

}

void Game::render()
{
	for (auto it : fl_GObjects)
	{
		it->render();
	}
}
void Game::Update(const uint64_t delta)
{

}
void Game::setKey(const int key, const int action)
{
	keys[key] = action;
}
bool Game::init(const glm::ivec2& boardSize, const std::string& ExecutablePath)
{
	ResourceManager::SetExecutablePath(ExecutablePath);
	auto DefaultShaderProgram = ResourceManager::loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
	if (!DefaultShaderProgram)
	{
		std::cerr << "Can't create shader program: " << "DefaultShader" << std::endl;
		system("pause");
		return false;
	}

	auto SpriteShaderProgram = ResourceManager::loadShaders("SpriteShader", "res/shaders/vertex_sprite.txt", "res/shaders/fragment_sprite.txt");
	if (!DefaultShaderProgram)
	{
		std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
		system("pause");
		return false;
	}
	std::vector<std::string> figures = { "black_castle", "black_knight", "black_bishop", "black_queen", "black_king", "black_pawn", "white_castle", "white_knight", "white_bishop", "white_queen", "white_king", "white_pawn" };
	ResourceManager::loadTextureAtlas("Figures", "res/textures/GameObjects_Atlas.png", figures, 67, 67);
	ResourceManager::loadSprite("Figure_black", "Figures", "SpriteShader", 135, 135, "black_pawn");
	ResourceManager::loadSprite("Figure_white", "Figures", "SpriteShader", 135, 135, "white_pawn");
	ResourceManager::loadTexture("Desk", "res/textures/Desk.png");
	ResourceManager::loadTexture("allowed_cell", "res/textures/green_quad.png");

	ResourceManager::loadSprite("sprite_Desk", "Desk", "SpriteShader", m_BoardSize.x, m_BoardSize.y, "");

	ResourceManager::loadSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", m_BoardSize.x / 8u, m_BoardSize.y / 8u, "");

	glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(m_BoardSize.x), 0.f, static_cast<float>(m_BoardSize.y), -100.f, 100.f);

	SpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

	SpriteShaderProgram->use();
	SpriteShaderProgram->setInt("tex", 0);
	SpriteShaderProgram->setMatrix4("projectionMat", projectionMatrix);

	GObject* desk = new Desk;
	desk->SetSprite("sprite_Desk", "Desk", "SpriteShader", m_BoardSize.x, m_BoardSize.y, "");
	GObject* figures_black[9];
	GObject* figures_white[9];
	for (int it = 0; it < 9; ++it)
	{
		figures_black[it] = new Figure;
		figures_white[it] = new Figure;

		figures_black[it]->SetSprite("Figure_black", "Figures", "SpriteShader", 135, 135, "black_pawn");
		figures_white[it]->SetSprite("Figure_white", "Figures", "SpriteShader", 135, 135, "white_pawn");
	}

	int it_Figures_black = 0;
	int it_Figures_white = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			if (BoardGraph[i][j] == 2)
			{
				figures_black[it_Figures_black]->Translate(glm::vec3(7 - i, j, 0));
				++it_Figures_black;
			}
			else if (BoardGraph[i][j] == 1)
			{
				figures_white[it_Figures_white]->Translate(glm::vec3(7 - i, j, 0));
				++it_Figures_white;
			}
		}
	}
	return true;
}

void Game::setBoardSize(const glm::ivec2 new_BoardSize)
{
	m_BoardSize = new_BoardSize;
}

glm::ivec2 Game::Get_BoardSize()
{
	return m_BoardSize;
}