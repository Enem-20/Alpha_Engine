#include "../Resources/ResourceManager.h"
#include "Desk.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Game.h"

Desk::Desk()
{
	model = glm::scale(model, glm::vec3(1080, 1080, 0));
	Game::desk = this;
}

void Desk::render()
{
	sprite->render(model);
}