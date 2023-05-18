#pragma once

#ifndef COMPONENT
#define COMPONENT

#include "../../src/Resources/ResourceBase.h"

#include <string>
#include <memory>

class GameObject;

class Component : public ResourceBase
{
public:
	Component(const std::string& name = "", const std::shared_ptr<GameObject>& gameObject = nullptr);
	Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject) noexcept;
	Component(Component&& component) noexcept;
	Component(const Component& component);

	~Component();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update(uint32_t currentImage) = 0;
	virtual void FixedUpdate() = 0;
	virtual void LastUpdate() = 0;

	//Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject)
	//	: name(name)
	//	, gameObject(gameObject)
	//{}
	std::shared_ptr<GameObject> GetGameObject() const;
	std::weak_ptr<GameObject> gameObject;
};
#endif //COMPONENT


struct ComponentView {
	ComponentView(std::shared_ptr<void> Data) : Data(Data) {}
	~ComponentView() { Data = nullptr; }
	template<class ComponentType>
	std::shared_ptr<ComponentType> getComponentFromView() {
		return std::reinterpret_pointer_cast<ComponentType>(Data);
	}
private:
	std::shared_ptr<void> Data;
};