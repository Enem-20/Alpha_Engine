#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "API/ExportPropety.h"

#include "Resources/ResourceBase.h"

#include <string>
#include <memory>

class GameObject;

class DLLEXPORT Component : public ResourceBase
{
public:
	Component(std::string_view name = "", const std::shared_ptr<GameObject>& gameObject = nullptr);
	Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject) noexcept;
	Component(Component&& component) noexcept;
	Component(const Component& component);

	~Component();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update(uint32_t currentFrame) = 0;
	virtual void FixedUpdate() = 0;
	virtual void LastUpdate() = 0;

	std::shared_ptr<GameObject> GetGameObject();
	std::weak_ptr<GameObject> gameObject;
};

struct DLLEXPORT ComponentView {
	ComponentView(std::shared_ptr<void> Data);
	ComponentView(const ComponentView& componentView);
	~ComponentView();
	template<class ComponentType>
	std::shared_ptr<ComponentType> getComponentFromView();
private:
	std::shared_ptr<void> Data;
};

template<class ComponentType>
std::shared_ptr<ComponentType> ComponentView::getComponentFromView() {
	return std::reinterpret_pointer_cast<ComponentType>(Data);
}

#endif //COMPONENT