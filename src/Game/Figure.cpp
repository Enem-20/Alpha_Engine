#include "Figure.h"
#include "../Resources/ResourceManager.h"

Figure::Figure()
{
	model = glm::scale(model, glm::vec3(135,135, 0));
}

void Figure::Search_path(bool BoardGraph[8][8])
{

}