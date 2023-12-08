#include "UIelement.h"

size_t UIelement::ID = 0;

UIelement::UIelement(std::string_view name, std::shared_ptr<GameObject> gameObject)
	: Component(name, gameObject)
	, parent(parent)
{}

UIelement::UIelement(UIelement&& uiElement) noexcept
	: elements(std::move(uiElement.elements))
	, parent(std::move(uiElement.parent.lock()))
	, Component(std::move(uiElement))
{
	++ID;
}

UIelement::UIelement(const UIelement& uiElement)
	: elements(uiElement.elements)
	, parent(uiElement.parent.lock())
	, Component(uiElement)
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