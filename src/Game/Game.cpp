#define Debut_value Game::ai.Debut->childs.front()->value

#include "Game.h"
#include "../GLPref/GLPref.h"

#include "../Resources/ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <glm/gtc/matrix_transform.hpp>
#include<glm/vec2.hpp>
#include<glm/vec3.hpp>
#include<glm/mat4x4.hpp>

#include <iostream>

Game::Game()
{
	Game::ECurrentGameFase = Game::EGameFase::Debut;
	//0 - free slot,  1 - white figure, 2 - black figure
	int BoardGraph[8][8] =
	{
	0,0,0,0,0,2,2,2,
	0,0,0,0,0,2,2,2,
	0,0,0,0,0,2,2,2,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	1,1,1,0,0,0,0,0,
	1,1,1,0,0,0,0,0,
	1,1,1,0,0,0,0,0
	};

	int Zones[8][8] =
	{
	0,0,0,0,-100,-200,-300,-400,
	0,0,5,5,-100,-200,-300,-300,
	0,0,10,5,5,-100,-200,-200,
	0,0,11,10,5,5,-100,-100,
	0,0,11,10,10,5,5,0,
	0,0,0,11,11,10,5,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0
	};

	int visited[8][8] =
	{
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0
	};

	this->Zones = new int* [8];
	this->BoardGraph = new int* [8];
	this->TargetGraph = new int* [8];
	this->visited = new bool* [8];
	for (int i = 0; i < 8; ++i)
	{
		this->BoardGraph[i] = new int[8];
		this->TargetGraph[i] = new int[8];
		this->Zones[i] = new int[8];
		this->visited[i] = new bool[8];
	}

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			TargetGraph[i][j] = BoardGraph[i][j];
			this->BoardGraph[i][j] = BoardGraph[i][j];
			this->Zones[i][j] = Zones[i][j];
			this->visited[i][j] = visited[i][j];
		}
	}

	MainWindow = GLPref::Mainwindow;
}
Game::~Game()
{

}

bool Game::init(const glm::ivec2& boardSize, const std::string& ExecutablePath)
{
	m_BoardSize = boardSize;
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

void Game::AI::CollectMoves()
{
	for (auto it : figures_black)
	{
		um_moves.emplace(FindPaths::GetMove(it));
	}
}

void Game::AI::CollectMoves(std::function<Node* ()> Debut)
{
	root = Debut();
	this->Debut = root;
}
void Game::AI::Go()
{
	int max = 0;
	switch (Game::ECurrentGameFase)
	{
	case Game::EGameFase::Debut:
		if (Game::Moves_count_black == 0 && Game::BoardGraph[Game::ai.Debut->value.second->coordinate.x][Game::ai.Debut->value.second->coordinate.y] == 0)
		{
			Game::BoardGraph[Game::ai.Debut->value.first->cellposition.x][Game::ai.Debut->value.first->cellposition.y] = 0;
			Game::ai.Debut->value.first->Translate(glm::ivec3(Game::ai.Debut->value.second->coordinate, 0));
			Game::BoardGraph[Game::ai.Debut->value.second->coordinate.x][Game::ai.Debut->value.second->coordinate.y] = 2;

			++Game::Moves_count_black;
			Game::ECurrentFractinMove = Game::EGameFractionMove::White;
			return;
		}
		if (!Game::ai.Debut->childs.empty() && Game::BoardGraph[Debut_value.second->coordinate.x][Debut_value.second->coordinate.y] == 0)
		{
			Game::BoardGraph[Debut_value.first->cellposition.x][Debut_value.first->cellposition.y] = 0;
			Debut_value.first->Translate(glm::ivec3(Debut_value.second->coordinate, 0));
			Game::BoardGraph[Debut_value.second->coordinate.x][Debut_value.second->coordinate.y] = 2;

			++Game::Moves_count_black;
			Game::ai.Debut = Game::ai.Debut->childs.front();
			Game::ECurrentFractinMove = Game::EGameFractionMove::White;
		}
		else if (Game::ai.Debut->childs.empty())
		{
			Game::ECurrentGameFase = Game::EGameFase::Begin;
			Game::ECurrentFractinMove = Game::EGameFractionMove::White;
		}
		else
		{
			std::list<Node*>::iterator iter = Game::ai.Debut->childs.begin();
			while (iter != Game::ai.Debut->childs.cend())
			{
				if (Game::BoardGraph[(*iter)->value.second->coordinate.x][(*iter)->value.second->coordinate.y] == 0)
				{
					Game::BoardGraph[(*iter)->value.first->cellposition.x][(*iter)->value.first->cellposition.y] = 0;
					(*iter)->value.first->Translate(glm::ivec3((*iter)->value.second->coordinate, 0));
					Game::BoardGraph[(*iter)->value.second->coordinate.x][(*iter)->value.second->coordinate.y] = 2;

					++Game::Moves_count_black;
					Game::ai.Debut = *iter;
					Game::ECurrentFractinMove = Game::EGameFractionMove::White;
					break;
				}
				++iter;
			}
			if (iter == Game::ai.Debut->childs.cend())
			{
				Game::ECurrentGameFase = Game::EGameFase::Begin;
				Game::ECurrentFractinMove = Game::EGameFractionMove::White;
			}
		}
		break;
	case Game::EGameFase::Begin:
		ai.CollectMoves();
		Figure* figure;
		for (auto it : um_moves)
		{
			if (it.second->value > max)
			{
				max = it.second->value;
				figure = it.first;
			}
		}
		Game::BoardGraph[figure->cellposition.x][figure->cellposition.y] = 0;
		Game::BoardGraph[um_moves[figure]->coordinate.x][um_moves[figure]->coordinate.y] = 2;
		figure->Translate(glm::vec3(um_moves[figure]->coordinate, 0));

		++Game::Moves_count_black;
		Game::ECurrentFractinMove = Game::EGameFractionMove::White;
		figure = nullptr;
		Game::ai.General_cost = 0;
		break;
	case Game::EGameFase::Mid:
		break;
	case Game::EGameFase::End:
		break;
	}
	
}