#include "AllowedCell.h"
#include "../Resources/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

AllowedCell::AllowedCell(glm::vec2 Boardposition)
{
	model = glm::scale(model, glm::vec3(135, 135, 0));
	Translate(glm::vec3(Boardposition, 0));
	cellposition = Boardposition;
}

void AllowedCell::render()
{
	sprite->render(model);
}