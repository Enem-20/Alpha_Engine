#pragma once

#include <list>

#include "Node.h"
#include "../Game/Figure.h"
#include "../Algorithms/Move.h"

Node* StandartDebut()
{
	Node* root;
	Node* tree;

	Figure* figure;

	for (auto it : Game::figures_black)
	{
		if (it->cellposition.x == 2 && it->cellposition.y == 6)
		{
			figure = it;
		}
	}

	root = tree = new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(2, 4))));

	for (auto it : Game::figures_black)
	{
		if (it->cellposition.x == 1 && it->cellposition.y == 6)
		{
			figure = it;
		}
	}

	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(3, 4)))));
	tree = tree->childs.front();
	for (auto it : Game::figures_black)
	{
		if (it->cellposition.x == 2 && it->cellposition.y == 5)
		{
			figure = it;
		}
	}
	
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(3,5)))));
	tree = tree->childs.front();
	for (auto it : Game::figures_black)
	{
		if (it->cellposition.x == 0 && it->cellposition.y == 5)
		{
			figure = it;
		}
	}
	Figure* buf = figure;
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(2, 3)))));
	tree = tree->childs.front();
	for (auto it : Game::figures_black)
	{
		if (it->cellposition.x == 0 && it->cellposition.y == 7)
		{
			figure = it;
		}
	}
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(4, 5)))));
	tree = tree->childs.front();
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(buf, new Move(glm::ivec2(2, 2)))));

	///////////////////////////////////////////////////////////////////////////////////////

	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(5, 5)))));
	Node* save = tree;
	tree = tree->childs.back();
	for (auto it : Game::figures_black)
	{
		if (it->cellposition.x == 2 && it->cellposition.y == 7)
		{
			figure = it;
		}
	}
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(6, 5)))));
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(4, 5)))));
	tree = save;
	save = nullptr;
	///////////////////////////////////////////////////////////////////////////////////////
	tree = tree->childs.front();
	buf = nullptr;
	for (auto it : Game::figures_black)
	{
		if (it->cellposition.x == 2 && it->cellposition.y == 7)
		{
			figure = it;
		}
	}
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(2, 1)))));
	tree->childs.push_back(new Node(std::pair<Figure*, Move*>(figure, new Move(glm::ivec2(2, 3)))));
	return root;
}