#include "UIelement.h"


size_t UIelement::ID = 0;

UIelement::UIelement(std::string name, std::shared_ptr<GameObject> gameObject)
	: Component(name, gameObject)
{}

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
