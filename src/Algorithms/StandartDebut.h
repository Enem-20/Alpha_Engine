#pragma once

#include <list>

#include "Node.h"
#include "../Game/Figure.h"
#include "../Algorithms/Move.h"

std::queue<std::pair<Figure*, Move*>> StandartDebut()
{
	std::queue<std::pair<Figure*, Move*>> result;


	//auto comp = [](Figure* first, Figure* second)
	//{
	//	return(first->cellposition.x < second->cellposition.x && first->cellposition.y > second->cellposition.y);
	//};
	//std::priority_queue<Figure*, decltype(comp)> line;
	for (int i = 0; i < 2; ++i)
	{
		Game::ai.outside_layer.push_back(Game::figures_black[glm::ivec2(i, 5)]);
	}
	for (int i = 6; i < 8; ++i)
	{
		Game::ai.outside_layer.push_back(Game::figures_black[glm::ivec2(2, i)]);
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 6; j < 8; ++j)
		{
			Game::ai.delivery.push_back(Game::figures_black[glm::ivec2(i, j)]);
		}
	}


	int lines = 0;
	int columns = 7;

	auto it_beg = Game::ai.outside_layer.begin();
	auto it_end = --Game::ai.outside_layer.end();
	for (int i = 0; i < 2; ++i)
	{
		result.push(std::pair<Figure*, Move*>(*(it_beg), new Move(glm::ivec2(lines++, 4))));
		result.push(std::pair<Figure*, Move*>(*(it_end), new Move(glm::ivec2(3, columns--))));
		++it_beg;
		--it_end;
	}
	result.push(std::pair<Figure*, Move*>(Game::ai.outside_layer.front(), new Move(glm::ivec2(0, 3))));
	result.push(std::pair<Figure*, Move*>(Game::ai.outside_layer.back(), new Move(glm::ivec2(4, 7))));

	lines = 2;
	columns = 5;
	for (int i = 0; i < 2; ++i)
	{
		result.push(std::pair<Figure*, Move*>(Game::ai.delivery.front(), new Move(glm::ivec2(0,columns))));
		result.push(std::pair<Figure*, Move*>(Game::ai.delivery.back(), new Move(glm::ivec2(lines, 7))));
		--columns;
		++lines;
	}
	return result;
}