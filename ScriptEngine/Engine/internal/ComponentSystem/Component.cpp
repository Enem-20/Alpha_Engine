#include "Component.h"

Component::Component(std::string_view name, const std::shared_ptr<GameObject>& gameObject)
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
}

std::shared_ptr<GameObject> Component::GetGameObject()
{
	return gameObject.lock();
}

ComponentView::ComponentView(std::shared_ptr<void> Data) : Data(Data) {}
ComponentView::ComponentView(const ComponentView& componentView)
	: Data(componentView.Data)
{

}
ComponentView::~ComponentView() { Data = nullptr; }