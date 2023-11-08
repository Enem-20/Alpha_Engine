#pragma once

#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "API/ExportPropety.h"

#include "Resources/ResourceManager.h"

#include "UI/Panel.h"
#include "ComponentSystem/Component.h"
#include "Resources/ResourceBase.h"


#include <type_traits>
#include <list>
#include <vector>
#include <unordered_map>
#include <typeinfo>
#include <string>
#include <memory>


#include <glm/glm.hpp>


class Transform;
class LuaScript;
class Sprite;
class Button;
class RenderPipeline;
class CommandBuffer;


class DLLEXPORT GameObject : public ResourceBase
{
	friend class Serializer;
	friend class DeserializerObject;
public:
public:
	GameObject(const GameObject& gameObject);
	GameObject(const std::string& name);
	void operator=(const GameObject& gameObject);
	GameObject(GameObject&&) = delete;
	virtual ~GameObject();


	void Translate(const glm::vec3& position);
	void Teleport(const glm::vec3& position);
	void Rotate(const glm::vec3& rotation);
	void Scale(const glm::vec3& scale);

	void Start();
	void Update(uint32_t currentImage);

	std::string& Name();
	virtual void render(CommandBuffer& commandBuffer, RenderPipeline& renderPipeline, uint32_t currentFrame);

	void AddChild(std::shared_ptr<GameObject> gameObject);
	std::shared_ptr<GameObject> GetChild(int i);

	template<class ComponentType>
	void addComponent(std::shared_ptr<ComponentType> component);

	template<class ComponentType>
	void removeComponent(const std::string& name);

	template<class ComponentType>
	std::shared_ptr<ComponentType> getComponent(const std::string& name);

	template<class ComponentType>
	std::unordered_map<std::string, ComponentView>* getComponentsWithType();
public:
	std::unordered_map<std::string, std::unordered_map<std::string, ComponentView>> components;

	std::vector<std::shared_ptr<GameObject>> children;

	std::weak_ptr<GameObject> parent;

	size_t ID;

	GENERATETYPE(GameObject)
protected:
	static size_t counter;
	void SetColliderTransform(std::shared_ptr<Transform> transform);
private:

	GameObject(size_t ID);
};

template<class ComponentType>
void GameObject::addComponent(std::shared_ptr<ComponentType> component) {
	static_assert(std::is_base_of<Component, ComponentType>::value || std::is_same<Component, ComponentType>::value, "ComponentType must inherit from Component or be a Component");
	component->gameObject = ResourceManager::template getResource<GameObject>(this->name);

	auto componentsByType = components.find(ComponentType::type);
	if (componentsByType != components.end()) {
		componentsByType->second.emplace(component->name, ComponentView{ std::reinterpret_pointer_cast<void>(component) });
	}
	else {
		components[ComponentType::type].emplace(component->name, ComponentView{ std::reinterpret_pointer_cast<void>(component) });
	}
}

template<class ComponentType>
void GameObject::removeComponent(const std::string& name) {
	size_t currentIndex = 0;

	auto componentsByType = components.find(ComponentType::type);

	if (componentsByType != components.end())
		componentsByType->second.erase(name);
}

template<class ComponentType>
std::shared_ptr<ComponentType> GameObject::getComponent(const std::string& name) {
	static_assert(std::is_base_of<Component, ComponentType>::value || std::is_same<Component, ComponentType>::value, "ComponentType must inherit from Component or be a Component");
	auto componentsByType = components.find(ComponentType::type);

	if (componentsByType != components.end()) {
		auto component = componentsByType->second.find(name);

		if (component != componentsByType->second.end()) {
			return component->second.getComponentFromView<ComponentType>();
		}
	}
		
	return nullptr;
}

template<class ComponentType>
std::unordered_map<std::string, ComponentView>* GameObject::getComponentsWithType() {
	static_assert(std::is_base_of<Component, ComponentType>::value || std::is_same<Component, ComponentType>::value, "ComponentType must inherit from Component or be a Component");

	auto componentsByType = components.find(ComponentType::type);

	if (componentsByType != components.end()) {
		return &componentsByType->second;
	}

	return nullptr;
}

#endif // !GAMEOBJECT