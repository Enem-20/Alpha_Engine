#pragma once

#ifndef UIELEMENT
#define UIELEMENT

#include "../../ComponentSystem/src/Component.h"

#include <sol/sol.hpp>
#include <glm/vec2.hpp>

#include <list>
#include <memory>

class GameObject;

class UIelement : public Component
{
public:
	UIelement(const std::string& name = "", std::shared_ptr<GameObject> gameObject = nullptr);
	UIelement(const UIelement& uiElement);
	UIelement(UIelement&& uiElement) noexcept;

	virtual void AddListener(const sol::protected_function& func);

	virtual void executeOnClicks();

	//void setParamCollider();
	//virtual void OnExecute() = 0;

	virtual void translate(const glm::vec2& newPos) = 0;
	//virtual void render(glm::mat4 model) = 0;

	//std::shared_ptr<Physics::Collider> collider;
protected:
	std::list<sol::protected_function> elements;
	static size_t ID;
};

size_t UIelement::ID = 0;

UIelement::UIelement(const std::string& name, std::shared_ptr<GameObject> gameObject) 
	: Component(name, gameObject)
{}

UIelement::UIelement(UIelement&& uiElement) noexcept
{
	++ID;
}

UIelement::UIelement(const UIelement& uiElement)
	: elements(uiElement.elements)
{
	++ID;
}

void UIelement::AddListener(const sol::protected_function& func)
{
	elements.push_back(func);
}

void UIelement::executeOnClicks()
{
	for (auto it : elements)
	{
		it();
	}
}

#endif //UIELEMENT