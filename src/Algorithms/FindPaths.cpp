#include <iostream>

#include "FindPaths.h"
#include "../Game/Game.h"

std::pair<Figure*, Move*> FindPaths::GetMove(Figure* figure)
{
	int start_value;
	std::pair<Figure*, Move*> Best;
	Best.first = figure;
	int value = Research_cross(figure->cellposition);
	value += Game::Zones[figure->cellposition.x][figure->cellposition.y];
	start_value = value;
	Game::ai.General_cost += value;
	Best.second = new Move(glm::ivec2(figure->cellposition.x, figure->cellposition.y), value);
	Game::visited[figure->cellposition.x][figure->cellposition.y] = true;
	
	glm::ivec2 start = figure->cellposition;

	if (start.x + 1 < 8 && Game::BoardGraph[start.x + 1][start.y] == 0)
	{
		value = Game::Zones[start.x + 1][start.y];
		value += Research_cross(glm::ivec2(start.x + 1, start.y));
		if (value > Best.second->value)
		{
			Best.second->value = value;
			Best.second->coordinate = glm::ivec2(start.x + 1, start.y);
		}
		
		Game::visited[start.x + 1][start.y] = true;
	}

	if (start.x - 1 >= 0 && Game::BoardGraph[start.x - 1][start.y] == 0)
	{
		value = Game::Zones[start.x - 1][start.y];
		value += Research_cross(glm::ivec2(start.x - 1, start.y));
		if(value > Best.second->value)
		{
			Best.second->value = value;
			Best.second->coordinate = glm::ivec2(start.x - 1, start.y);
		}
		Game::visited[start.x - 1][start.y] = true;
	}

	if (start.y + 1 < 8 && Game::BoardGraph[start.x][start.y + 1] == 0)
	{
		value = Game::Zones[start.x][start.y + 1];
		value += Research_cross(glm::ivec2(start.x, start.y + 1));
		if (value > Best.second->value)
		{
			Best.second->value = value;
			Best.second->coordinate = glm::ivec2(start.x, start.y + 1);
		}
		Game::visited[start.x][start.y + 1] = true;
	}
	
	if (start.y - 1 >= 0 && Game::BoardGraph[start.x][start.y - 1] == 0)
	{
		value = Game::Zones[start.x][start.y - 1];
		value += Research_cross(glm::ivec2(start.x, start.y - 1));
		if (value > Best.second->value)
		{
			Best.second->value = value;
			Best.second->coordinate = glm::ivec2(start.x, start.y - 1);
		}
		Game::visited[start.x][start.y - 1] = true;
	}

	q.push(start);

	glm::ivec2 prev(-1, -1);

	int depth = 1;
	while (!q.empty())
	{
		if (q.front().x + 1 < 8 && Game::BoardGraph[q.front().x + 1][q.front().y] != 0 && q.front().x + 1 < 8 && Game::BoardGraph[q.front().x + 1][q.front().y] != 3)
		{
			if (q.front().x + 2 < 8 && Game::BoardGraph[q.front().x + 2][q.front().y] == 0 && !Game::visited[q.front().x + 2][q.front().y])
			{
				value = Game::Zones[q.front().x + 2][q.front().y];
				value += Research_cross(glm::ivec2(q.front().x + 2, q.front().y));
				if (value > Best.second->value)
				{
					Best.second->value = value;
					Best.second->coordinate = glm::ivec2(start.x + 2, start.y);
				}
				q.push(glm::ivec2(q.front().x + 2, q.front().y));
				Game::visited[q.front().x + 2][q.front().y] = true;
			}
			
		}
		if (q.front().x - 1 >= 0 && Game::BoardGraph[q.front().x - 1][q.front().y] != 0 && q.front().x - 1 >= 0 && Game::BoardGraph[q.front().x - 1][q.front().y] != 3)
		{
			if (q.front().x - 2 >= 0 && Game::BoardGraph[q.front().x - 2][q.front().y] == 0 && !Game::visited[q.front().x - 2][q.front().y])
			{
				value = Game::Zones[q.front().x - 2][q.front().y];
				value += Research_cross(glm::ivec2(q.front().x - 2, q.front().y));
				if (value > Best.second->value)
				{
					Best.second->value = value;
					Best.second->coordinate = glm::ivec2(start.x - 2, start.y);
				}
				q.push(glm::ivec2(q.front().x - 2, q.front().y));
				Game::visited[q.front().x - 2][q.front().y] = true;
			}
		}

		if (q.front().y + 1 < 8 && Game::BoardGraph[q.front().x][q.front().y + 1] != 0 && Game::BoardGraph[q.front().x][q.front().y + 1] != 3)
		{
			if (q.front().y + 2 < 8 && Game::BoardGraph[q.front().x][q.front().y + 2] == 0 && !Game::visited[q.front().x][q.front().y + 2])
			{
				value = Game::Zones[q.front().x][q.front().y + 2];
				value += Research_cross(glm::ivec2(q.front().x, q.front().y + 2));
				if (value > Best.second->value)
				{
					Best.second->value = value;
					Best.second->coordinate = glm::ivec2(start.x, start.y + 2);
				}
				q.push(glm::ivec2(q.front().x, q.front().y + 2));
				Game::visited[q.front().x][q.front().y + 2] = true;
			}
		}

		if (q.front().y - 1 >= 0 && Game::BoardGraph[q.front().x][q.front().y - 1] != 0 && Game::BoardGraph[q.front().x][q.front().y - 1] != 3)
		{
			if (q.front().y - 2 >= 0 && Game::BoardGraph[q.front().x][q.front().y - 2] == 0 && !Game::visited[q.front().x][q.front().y - 2])
			{
				value = Game::Zones[q.front().x][q.front().y - 2];
				value += Research_cross(glm::ivec2(q.front().x, q.front().y - 2));
				if (value > Best.second->value)
				{
					Best.second->value = value;
					Best.second->coordinate = glm::ivec2(start.x, start.y - 2);
				}
				q.push(glm::ivec2(q.front().x, q.front().y - 2));
				Game::visited[q.front().x][q.front().y - 2] = true;

				
			}
		}
		++depth;
		prev = q.front();
		q.pop();
	}
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			Game::visited[i][j] = false;
		}
	}

	if (start_value < 0 && Best.second->value > 0)
	{
		Best.second->value *= -1;
	}
	Best.second->value = Best.second->value - start_value;
	return Best;
}

int FindPaths::Research_cross(glm::ivec2 current)
{
	int value = 0;
	if (current.x + 1 < 8 && Game::BoardGraph[current.x + 1][current.y] == 2 && !Game::visited[current.x + 1][current.y])
	{
		value += 5;
	}
	if (current.x - 1 >= 0 && Game::BoardGraph[current.x - 1][current.y] == 2 && !Game::visited[current.x - 1][current.y])
	{
		value += 5;
	}
	if (current.y + 1 < 8 && Game::BoardGraph[current.x][current.y + 1] == 2 && !Game::visited[current.x][current.y + 1])
	{
		value += 5;
	}
	if (current.y - 1 >= 0 && Game::BoardGraph[current.x][current.y - 1] == 2 && !Game::visited[current.x][current.y - 1])
	{
		value += 5;
	}
	return value;
} 