#include "Figure.h"
#include "../Resources/ResourceManager.h"
#include "Game.h"

#include <queue>

Figure::Figure()
{
	model = glm::scale(model, glm::vec3(135,135, 0));
	fraction = -1;
}

void Figure::Search_path(glm::ivec2 start, int fraction)
{
	std::queue<glm::ivec2> q;

	q.push(start);

	glm::ivec2 current;

	if (start.y + 1 < 8 && Game::BoardGraph[start.x][start.y + 1] == 0)
	{
		Game::BoardGraph[start.x][start.y + 1] = 3;
		allowedCell.push_back(new AllowedCell(glm::ivec2(start.x, start.y + 1)));
		allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
	}

	if (start.x + 1 < 8 && Game::BoardGraph[start.x + 1][start.y] == 0)
	{
		Game::BoardGraph[start.x + 1][start.y] = 3;
		allowedCell.push_back(new AllowedCell(glm::ivec2(start.x + 1, start.y)));
		allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
	}

	if (start.x - 1 >= 0 && Game::BoardGraph[start.x - 1][start.y] == 0)
	{
		Game::BoardGraph[start.x - 1][start.y] = 3;
		allowedCell.push_back(new AllowedCell(glm::ivec2(start.x - 1, start.y)));
		allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
	}

	if (start.y - 1 >= 0 && Game::BoardGraph[start.x][start.y - 1] == 0)
	{
		Game::BoardGraph[start.x][start.y - 1] = 3;
		allowedCell.push_back(new AllowedCell(glm::ivec2(start.x, start.y - 1)));
		allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
	}

	while (!q.empty())
	{
		current = q.front();
		if (current.y + 1 < 8 && (Game::BoardGraph[current.x][current.y + 1] == 2 || Game::BoardGraph[current.x][current.y + 1] == 1))
		{
			if (current.y + 2 < 8 && Game::BoardGraph[current.x][current.y + 2] == 0)
			{
				Game::BoardGraph[current.x][current.y + 2] = 3;
				allowedCell.push_back(new AllowedCell(glm::ivec2(current.x, current.y + 2)));
				allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
				q.push(glm::ivec2(current.x, current.y + 2));
			}
		}

		if (current.x + 1 < 8 && (Game::BoardGraph[current.x + 1][current.y] == 2 || Game::BoardGraph[current.x + 1][current.y] == 1))
		{
			if (current.x + 2 < 8 && Game::BoardGraph[current.x + 2][current.y] == 0)
			{
				Game::BoardGraph[current.x + 2][current.y] = 3;
				allowedCell.push_back(new AllowedCell(glm::ivec2(current.x + 2, current.y)));
				allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
				q.push(glm::ivec2(current.x + 2, current.y));
			}
		}

		if (current.x - 1 >= 0 && (Game::BoardGraph[current.x - 1][current.y] == 2 || Game::BoardGraph[current.x - 1][current.y] == 1))
		{
			if (current.x - 2 >= 0 && Game::BoardGraph[current.x - 2][current.y] == 0)
			{
				Game::BoardGraph[current.x - 2][current.y] = 3;
				allowedCell.push_back(new AllowedCell(glm::ivec2(current.x - 2, current.y)));
				allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
				q.push(glm::ivec2(current.x - 2, current.y));
			}
		}

		if (current.y - 1 >= 0 && (Game::BoardGraph[current.x][current.y - 1] == 2 || Game::BoardGraph[current.x][current.y - 1] == 1))
		{
			if (current.y - 2 >= 0 && Game::BoardGraph[current.x][current.y - 2] == 0)
			{
				Game::BoardGraph[current.x][current.y - 2] = 3;
				allowedCell.push_back(new AllowedCell(glm::ivec2(current.x, current.y - 2)));
				allowedCell.back()->SetSprite("sprite_allowed_cell", "allowed_cell", "SpriteShader", Game::m_BoardSize.x / 8u, Game::m_BoardSize.y / 8u, "");
				q.push(glm::ivec2(current.x, current.y - 2));
			}
		}

		q.pop();
	}
}

void Figure::render()
{
	sprite->render(model);
	for (auto it : allowedCell)
	{
		it->render();
	}
}