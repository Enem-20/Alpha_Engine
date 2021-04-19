#include "GameObject.h"
#include "Game.h"
#include "../Scene/Hierarchy.h"

#include <typeinfo>

#include <../glm/glm/vec2.hpp>
#include <../glm/glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Resources/ResourceManager.h"


struct callAwake final
{
	void operator()(Components::LuaScript& l) { l.Awake(); }
};

GameObject::GameObject(std::string name,
	std::shared_ptr<RenderEngine::Sprite> sprite,
	glm::vec3 position,
	glm::ivec2 cellposition,
	glm::mat4 model,
	std::unordered_map<std::string, std::variant<Components::LuaScript>> Components)
	: name(name)
	, sprite(sprite)
	, position(position)
	, cellposition(cellposition)
	, model(model)
	, m_Components(Components)
{
	this->model = glm::mat4(1.f);

	if (sprite) 
	{ 
		this->model = glm::translate(this->model, position);
		this->model = glm::scale(this->model, glm::vec3(this->sprite->getSize(), 0));
	}
	else{ this->model = glm::scale(this->model, glm::vec3(135, 135, 0)); }

	for (auto& itComponents : m_Components)
	{
		std::visit(callAwake{}, itComponents.second);
	}

	Hierarchy::addObject(std::make_shared<GameObject>(*this));
}

GameObject::GameObject(const GameObject& gameObject)
{
	this->cellposition = gameObject.cellposition;
	this->model = gameObject.model;
	this->m_ShaderProgram = gameObject.m_ShaderProgram;
	this->name = gameObject.name;
	this->position = gameObject.position;
	this->sprite = gameObject.sprite;
	this->m_Components = gameObject.m_Components;
}

GameObject::~GameObject()
{
	sprite.reset();
	m_ShaderProgram.reset();
}

void GameObject::render()
{
	if (sprite) { sprite->render(model); }
}

void GameObject::Translate(glm::vec3 position)
{
	model = glm::mat4(1.f);

	cellposition.x = position.x / 8;
	cellposition.y = position.y / 8;
	this->position += position;

	model = glm::rotate(model, this->sprite->getRotation(), glm::vec3(0, 0, 1));
	model = glm::translate(model, this->position);
	model = glm::scale(model, glm::vec3(this->sprite->getSize(), 0));

	sprite->setPosition(position);
}

void GameObject::Rotate(const float rotation)
{
	glm::mat4 model(1.f);

	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 0));
}

std::shared_ptr<RenderEngine::Sprite> GameObject::GetSprite()
{
	return sprite;
}

void GameObject::SetSprite(const std::string& spriteName,
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

void GameObject::SetSpriteCopy(const std::shared_ptr<RenderEngine::Sprite> sprite)
{
	this->sprite = std::make_shared<RenderEngine::Sprite>(*sprite);
}

void GameObject::SetModel(glm::mat4&& model)
{
	this->model = std::move(model);
}