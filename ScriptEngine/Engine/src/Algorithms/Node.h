#pragma once

#include<list>

#include "../GameTypes/Figure.h"

class Move;

class Node
{
public:
	Node(std::pair<Figure*, Move*> value)
	{
		this->value = value;
	}
	std::pair<Figure*, Move*> value;
	std::list<Node*> childs;
};