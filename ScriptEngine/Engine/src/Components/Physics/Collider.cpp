#include "Collider.h"
#include "../../Game/Game.h"

#include <memory>

Collider::Collider()
{
	GetUpdater([&]()
	{
		for (size_t i = gObject->cellposition.x - (cell_size.x / 2); i < gObject->cellposition.x + (cell_size.x / 2); ++i)
		{
			for (size_t j = gObject->cellposition.y - (cell_size.y / 2); j < gObject->cellposition.y + (cell_size.y / 2); ++j)
			{
				if (Game::BoardGraph[i][j] == 1)
				{
					visitors.push_back(Game::figures_white[glm::ivec2(i, j)]);
				}
			}
		}
	});
}


glm::ivec2& Collider::Get_cell_size()
{
	return cell_size;
}

void Collider::Set_cell_size(const glm::ivec2 new_cell_size)
{
	cell_size = new_cell_size;
}

Figure* Collider::Get_Visitor(size_t concrete_visitor)
{
	auto it = visitors.begin();
	for (size_t i = 0; i != concrete_visitor; ++i)
	{
		++it;
	}

	return *it;
}

std::list<Figure*>& Collider::Get_Visitors()
{
	return visitors;
}
void Collider::GetUpdater(std::function<void()> updater)
{
	update = updater;
}