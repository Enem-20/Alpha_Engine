#include "GObject.h"
#include "Game.h"

#include <../glm/glm/vec2.hpp>
#include <../glm/glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Resources/ResourceManager.h"

GObject::GObject()
{
	//Game::fl_GObjects.push_back(this);
	glm::mat4 model(1.f);
	this->model = model;
	glm::vec3 position(0.f);
	this->position = position;
}

GObject::~GObject()
{
	sprite.reset();
	m_ShaderProgram.reset();
}

void GObject::render()
{
	sprite->render(model);
}

void GObject::InstanceRender()
{
	sprite->InstanceRender(model);
}

void GObject::Translate(glm::vec3 position)
{
	glm::mat4 Buf_model = glm::mat4(1.f);
	model = Buf_model;
	model = glm::scale(model, glm::vec3(135, 135, 0));

	cellposition = position;
	model = glm::translate(model, glm::vec3(position));
	//sprite->setPosition(position);
}

void GObject::Rotate(const float rotation)
{
	glm::mat4 model(1.f);

	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
}

std::shared_ptr<Renderer::Sprite> GObject::GetSprite()
{
	return sprite;
}

void GObject::SetSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight,
	const std::string& subTextureName)
{
	if (ResourceManager::getSprite(spriteName) == nullptr)
	{
		ResourceManager::loadSprite(spriteName, textureName, shaderName, spriteWidth, spriteHeight, subTextureName);
	}
	else
	{
		sprite = ResourceManager::getSprite(spriteName);
	}
}