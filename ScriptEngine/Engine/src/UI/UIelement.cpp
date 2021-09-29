#include "UIelement.h"

namespace UI
{
	size_t UIelement::ID = 0;
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
}