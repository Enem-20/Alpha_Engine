#include "Component.h"

Component::Component(const std::string& name, const std::shared_ptr<GameObject>& gameObject)
	: ResourceBase(name)
	, gameObject(gameObject)
{
	if (gameObject == nullptr) {
		//Paste hierarchy search here
	}
}

Component::Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject) noexcept
	: ResourceBase(std::move(name))
	, gameObject(gameObject)
{}

Component::Component(Component&& component) noexcept
	: ResourceBase(std::move(component.name))
	, gameObject(component.gameObject)
{}

Component::Component(const Component& component)
	: ResourceBase(component.name)
	, gameObject(component.gameObject)
{}

Component::~Component()
{
	//gameObject = nullptr;
}

std::shared_ptr<GameObject> Component::GetGameObject() const
{
	return gameObject.lock();
}