#include "UIelement.h"
#include "../GameTypes/GameObject.h"

#include <string>

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


	//void UIelement::setParamCollider()
	//{
	//	glm::vec2 leftBottom = glm::vec2(0.f), rightTop = glm::vec2(0.f);
	//	if (gameObject)
	//	{
	//		leftBottom.x = gameObject->transform->position.x;
	//		leftBottom.y = gameObject->transform->position.y;
	//		rightTop.x = gameObject->transform->position.x + gameObject->GetSprite()->getSize().x;
	//		rightTop.y = gameObject->transform->position.y + gameObject->GetSprite()->getSize().y;
	//	}
	//	collider->Update(leftBottom, rightTop);
	//}

	//UIelement::UIelement()
	//{
	//	glm::vec2 leftBottom, rightTop = glm::vec2(0.f);
	//	if (gameObject)
	//	{
	//		leftBottom.x = gameObject->transform->position.x - gameObject->GetSprite()->getSize().x / 2;
	//		leftBottom.y = gameObject->transform->position.y - gameObject->GetSprite()->getSize().y / 2;
	//		rightTop.x = gameObject->transform->position.x + gameObject->GetSprite()->getSize().x / 2;
	//		rightTop.y = gameObject->transform->position.y + gameObject->GetSprite()->getSize().y / 2;
	//	}
	//	collider = std::make_shared<Physics::Collider>(leftBottom, rightTop);
	//	name = "";
	//	model = glm::mat4(1.f);
	//}
}