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
#include <stack>

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
	0,0,0,0,-100,-200,-300,-300,
	0,0,100,0,0,-100,-200,-200,
	0,0,200,100,0,0,-100,-100,
	0,0,200,200,100,0,0,0,
	300,300,300,200,200,100,0,0,
	400,400,300,0,0,0,0,0,
	500,400,300,0,0,0,0,0
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

//void Game::AI::CollectMoves()
//{
//	for (auto it : figures_black)
//	{
//		um_moves.emplace(FindPaths::GetMove(it.second));
//	}
//}

void Game::AI::CollectMoves(std::function<std::queue<std::pair<Figure*, Move*>>()> Debut)
{
	Game::Debut = Debut();
}
void Game::AI::Go()
{
	int max = 0;
	switch (Game::ECurrentGameFase)
	{
	case Game::EGameFase::Debut:
		if (!Debut.empty())
		{
			Game::BoardGraph[Debut.front().first->cellposition.x][Debut.front().first->cellposition.y] = 0;
			Game::BoardGraph[Debut.front().second->coordinate.x][Debut.front().second->coordinate.y] = 2;
			Game::Debut.front().first->Translate(glm::vec3(Debut.front().second->coordinate, 0));
			Game::Debut.pop();
			Game::ECurrentFractinMove = Game::EGameFractionMove::White;
		}
		else
		{
			ECurrentGameFase = Game::EGameFase::Game;
		}
		break;
	case Game::EGameFase::Game:
		break;
	}
	
}

void Game::AI::Deliver()
{
	std::queue<glm::ivec2> q;
	
	glm::ivec2 finish(outside_layer.front()->cellposition);

	q.push(delivery.front()->cellposition);

	glm::ivec2 buf;

	struct KeyFuncs
	{
		size_t operator()(const glm::ivec2& k)const
		{
			return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
		}

		bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
		{
			return a.x == b.x && a.y == b.y;
		}
	};

	std::unordered_map<glm::ivec2, glm::ivec2, KeyFuncs> child_to_parent;

	while (!q.empty())
	{
		buf = glm::ivec2(q.front().x + 1, q.front().y);
		if (buf.x < 8 && buf != finish && !shell_bool::Get(visited, buf))
		{
			child_to_parent[buf] = q.front();
			if (buf == finish)
			{
				break;
			}
			q.push(buf);
			shell_bool::Get(visited, buf) = true;
		}
		buf = glm::ivec2(q.front().x - 1, q.front().y);
		if (buf.x >= 0 && buf == finish && !shell_bool::Get(visited, buf))
		{
			child_to_parent[buf] = q.front();
			if (buf == finish)
			{
				break;
			}
			q.push(buf);
			shell_bool::Get(visited, buf) = true;
			
		}
		buf = glm::ivec2(q.front().x, q.front().y + 1);
		if (buf.y < 8 && buf == finish && !shell_bool::Get(visited, buf))
		{
			child_to_parent[buf] = q.front();
			q.push(buf);
			if (buf == finish)
			{
				break;
			}
			shell_bool::Get(visited, buf) = true;	
		}
		buf = glm::ivec2(q.front().x, q.front().y - 1);
		if (buf.y >= 0 && buf == finish && !shell_bool::Get(visited, buf))
		{
			child_to_parent[buf] = q.front();
			q.push(buf);
			if (buf == finish)
			{
				break;
			}
			shell_bool::Get(visited, buf) = true;
		}
		q.pop();
	}

	std::stack<glm::ivec2> invert_path;
	if (buf != outside_layer.front()->cellposition)
	{
		invert_path.push(child_to_parent[buf]);
		buf = child_to_parent[buf];
	}
}