#include "GameObject.h"

#include "../Renderer/Sprite.h"
#include "../Scene/Hierarchy.h"
#include "../UI/Button.h"
#include "../Helpers/StringFuncs.h"

#include <../glm/glm/vec2.hpp>
#include <../glm/glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

size_t GameObject::counter = 0;
GameObject GameObject::Null;

GameObject::GameObject(std::string name,
	std::shared_ptr<Components::Transform> transform,
	std::shared_ptr<RenderEngine::Sprite> sprite,
	std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts,
	std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons,
	int render_priority)
	: transform(transform)
	, sprite(sprite)
	, scripts(scripts)
	, buttons(buttons)
	, render_priority(render_priority)
{
	onGrid = false;
	if (Hierarchy::getObject(name))
	{
		ID = counter ? ++counter : counter;
		this->name = name + std::to_string(ID);
	}
	else
	{
		ID = 0;
		this->name = name;
	}
	//transform->Translate(glm::vec3(0.f));
	//transform->Rotate(glm::vec3(0.f));
	if (this->transform != nullptr)
	{
		if (sprite) { this->transform->scale = glm::vec3(sprite->getSize(), 0.f); }
		this->transform->Scale(glm::vec3(0.f));
	}
	else
	{
		this->transform = std::make_shared<Components::Transform>(this->name);
		this->transform->Scale(glm::vec3(0.f));
	}
	this->render_priority = render_priority;



	Hierarchy::addObject(*this);
	if(onGrid)//Костыль
		Hierarchy::addGridObject(this->name);
	for (auto itScripts : scripts)
	{
		itScripts.second->gameObject = Hierarchy::getObject(this->name);
		itScripts.second->Awake();
	}
	for (auto button : buttons)
	{
		button.second->gameObject = Hierarchy::getObject(this->name);
		//button.second.setParamCollider();
	}
}

GameObject::GameObject(const GameObject& gameObject)
	: scripts(gameObject.scripts)
	, buttons(gameObject.buttons)
	, onGrid(gameObject.onGrid)
{
	this->sprite = gameObject.sprite;
	this->transform = std::make_shared<Components::Transform>(gameObject.transform->position, gameObject.transform->rotation, glm::vec3(0.f));
	if(sprite)
		this->transform->scale = glm::vec3(sprite->getSize(), 0.f);
	this->transform->Scale(glm::vec3(0.f));

	ID = 0;
	if (Hierarchy::getObject(gameObject.name))
	{
		while (Hierarchy::getObject(gameObject.name + std::to_string(ID)))
		{
			++ID;
		}
		this->name = gameObject.name + std::to_string(ID);
	}
	else
	{
		this->name = gameObject.name;
	}

	this->render_priority = gameObject.render_priority;
}

void GameObject::operator=(const GameObject& gameObject)
{
	buttons = gameObject.buttons;
	children = gameObject.children;
	ID = gameObject.ID + 1;
	this->name = StringFuncs::RemoveNumbersEnd(gameObject.name) + std::to_string(ID);
	++counter;
	onGrid = gameObject.onGrid;
	render_priority = gameObject.render_priority;
	scripts = gameObject.scripts;
	sprite = gameObject.sprite;
	transform = gameObject.transform;
}

GameObject::~GameObject()
{
	scripts.clear();
	buttons.clear();
	sprite.reset();
	transform.reset();
	children.clear();
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

void GameObject::Translate(const glm::vec3& position)
{
	if(onGrid)	//Костыль
		Hierarchy::removeGridObject(Input::GetCell(transform->position));
	transform->Translate(position);
	for (auto it : children)
	{
		it->Translate(position);
	}
	if(onGrid)//Костыль
		Hierarchy::addGridObject(this->name);
	Update();
}

void GameObject::Teleport(const glm::vec3& position)
{
	if(onGrid)//Костыль
		Hierarchy::removeGridObject(Input::GetCell(transform->position));
	transform->Teleport(position);
	for (auto& it : children)
	{
		it->Teleport(position);
	}
	if(onGrid)//Костыль
		Hierarchy::addGridObject(this->name);
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
	for (auto& it : buttons)
	{
		it.second->translate(transform->position);
	}

	//Teleport(transform->position);
}

std::shared_ptr<RenderEngine::Sprite> GameObject::GetSprite() const
{
	return sprite;
}

void GameObject::AddChild(const GameObject& gameObject)
{
	children.push_back(std::make_shared<GameObject>(gameObject));
}
GameObject& GameObject::GetChild(int i) const
{
	return *children[i];
}

GameObject& GameObject::toNull(GameObject& gameObject)
{
	gameObject.children.clear();
	gameObject.buttons.clear();
	gameObject.ID = -1;
	gameObject.name = "Null";
	gameObject.render_priority = -1;
	gameObject.scripts.clear();
	gameObject.sprite = nullptr;
	gameObject.transform = nullptr;
	
	return gameObject;
}

GameObject::GameObject(size_t ID)
{
	this->ID = ID;
}

GameObject GameObject::SetNull()
{
	Null = GameObject(-1);
	return Null;
}