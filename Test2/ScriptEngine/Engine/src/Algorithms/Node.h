#pragma once

#include<list>

#include "../Game/Figure.h"

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