#include "AllowedCell.h"
#include "../Resources/ResourceManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

AllowedCell::AllowedCell()
{
	model = glm::scale(model, glm::vec3(135, 135, 0));
}

void AllowedCell::SetSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight,
	const std::string& subTextureName)
{

}