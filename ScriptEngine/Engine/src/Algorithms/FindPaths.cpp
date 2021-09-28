#include <iostream>
#include <queue>

#include "FindPaths.h"
#include "../Game/Game.h"

//std::pair<Figure*, Move*> FindPaths::GetMove(Figure* figure)
//{
//	std::pair<Figure*, Move*> Best;
//	int value = 0;
//	
//	auto comp = [](Figure* first, Figure* second)
//	{
//		return(first->cellposition.x < second->cellposition.x&& first->cellposition.y > second->cellposition.y);
//	};
//	std::priority_queue < Figure*, decltype(comp)> pq;
//
//	for (auto it : Game::figures_black)
//	{
//		pq.emplace(it);
//	}
//
//	if (q.front().x + 1 < 8 && Game::BoardGraph[q.front().x + 1][q.front().y] == 0 && !Game::visited[q.front().x + 1][q.front().y])
//	{
//		if(Game)
//		Game::visited[q.front().x + 1][q.front().y] = true;
//	}
//	if (q.front().x - 1 < 8 && Game::BoardGraph[q.front().x - 1][q.front().y] == 0 && !Game::visited[q.front().x - 1][q.front().y])
//	{
//		Game::visited[q.front().x - 1][q.front().y] = true;
//	}
//	if (q.front().y + 1 < 8 && Game::BoardGraph[q.front().x][q.front().y + 1] == 0 && !Game::visited[q.front().x][q.front().y + 1])
//	{
//		Game::visited[q.front().x][q.front().y + 1] = true;
//	}
//	if (q.front().y - 1 < 8 && Game::BoardGraph[q.front().x][q.front().y - 1] == 0 && !Game::visited[q.front().x][q.front().y - 1])
//	{
//		Game::visited[q.front().x][q.front().y - 1] = true;
//	}
//
//
//	return Best;
//}
