#include "GameObject.h"

#include "../Scene/Hierarchy.h"
#include "../Resources/ResourceManager.h"
#include "../UI/Button.h"

#include <typeinfo>

#include <../glm/glm/vec2.hpp>
#include <../glm/glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

GameObject::GameObject(std::string name,
	std::shared_ptr<Components::Transform> transform,
	std::shared_ptr<RenderEngine::Sprite> sprite,
	std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts,
	std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons,
	int render_priority)
	: name(name)
	, transform(transform)
	, sprite(sprite)
	, scripts(scripts)
	, buttons(buttons)
	, render_priority(render_priority)
{
	transform->Translate(glm::vec3(0.f));
	transform->Rotate(glm::vec3(0.f));
	transform->Scale(glm::vec3(sprite->getSize(), 0.f));

	this->render_priority = render_priority;

	Hierarchy::addObject(*this);		
	for (auto itScripts : scripts)
	{
		itScripts.second->gameObject = Hierarchy::getObject(name);
		itScripts.second->Awake();
	}
	for (auto button : buttons)
	{
		button.second->gameObject = Hierarchy::getObject(name);
		//button.second.setParamCollider();
	}
}

GameObject::GameObject(const GameObject& gameObject)
	: transform(gameObject.transform)
	, scripts(gameObject.scripts)
	, buttons(gameObject.buttons)
{
	this->name = gameObject.name;
	this->sprite = gameObject.sprite;
	this->render_priority = gameObject.render_priority;
}

GameObject::~GameObject()
{
}

void GameObject::render()
{
	if (sprite)
	{
		sprite->render(transform->GetModel());
	}

	for (auto it : children)
	{
		it->render();
	}
}

void GameObject::Translate(glm::vec3 position)
{
	transform->Translate(position);
	for (auto it : children)
	{
		it->Translate(position);
	}

	Update();
}

void GameObject::Rotate(glm::vec3 rotation)
{
	transform->Rotate(std::move(rotation));
	for (auto it : children)
	{
		it->Rotate(rotation);
	}

	Update();
}

void GameObject::Scale(glm::vec3 scale)
{
	transform->Scale(std::move(scale));
	for (auto it : children)
	{
		it->Scale(scale);
	}

	Update();
}

void GameObject::Update()
{
	for (auto it : buttons)
	{
		//it.second->setParamCollider();
	}
}

std::shared_ptr<RenderEngine::Sprite> GameObject::GetSprite() const
{
	return sprite;
}

//void GameObject::SetSprite(const std::string& spriteName,
//	const std::string& textureName,
//	const std::string& shaderName,
//	const unsigned int spriteWidth,
//	const unsigned int spriteHeight,
//	const std::string& subTextureName)
//{
//	if (ResourceManager::getSprite(spriteName) == nullptr)
//	{
//		ResourceManager::loadSprite(spriteName, textureName, shaderName, spriteWidth, spriteHeight, subTextureName);
//	}
//	else
//	{
//		sprite = ResourceManager::getSprite(spriteName);
//	}
//}

void GameObject::AddChild(std::shared_ptr<GameObject> gameObject)
{
	children.push_back(gameObject);
}
std::shared_ptr<GameObject> GameObject::GetChild(int i) const
{
	return children[i];
}