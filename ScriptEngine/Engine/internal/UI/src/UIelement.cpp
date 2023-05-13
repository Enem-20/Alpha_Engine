#include "UIelement.h"

size_t UIelement::ID = 0;

UIelement::UIelement(const std::string& name, std::shared_ptr<GameObject> gameObject)
	: Component(name, gameObject)
{}

UIelement::UIelement(UIelement&& uiElement) noexcept
	: elements(std::move(uiElement.elements))
	, Component(std::move(uiElement))
{
	++ID;
}

UIelement::UIelement(const UIelement& uiElement)
	: elements(uiElement.elements)
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