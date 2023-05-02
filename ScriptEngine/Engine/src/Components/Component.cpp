#include "Component.h"
#include "../Scene/Hierarchy.h"


//Component::Component(std::string name, std::shared_ptr<GameObject> gameObject)
//	: name(name)
//	, gameObject(gameObject)
//{}
//Component::Component(std::string&& name, GameObject&& gameObject) noexcept
//	: name(std::move(name))
//	, gameObject(std::move(&gameObject))
//{}
//Component::~Component()
//{
//	gameObject = nullptr;
//}
//
//GameObject& Component::GetGameObject() const
//{
//	return *Hierarchy::getObject(name);
//}
