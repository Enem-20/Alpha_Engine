#pragma once

#ifndef COMPONENT
#define COMPONENT

#include <string>
#include <memory>

class GameObject;

class Component
{
public:
	Component(const std::string& name = "", const std::shared_ptr<GameObject>& gameObject = nullptr);
	Component(std::string&& name, GameObject&& gameObject) noexcept;
	Component(Component&& component) noexcept;
	Component(const Component& component);

	~Component();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void FixedUpdate() = 0;
	virtual void LastUpdate() = 0;

	//Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject)
	//	: name(name)
	//	, gameObject(gameObject)
	//{}
	GameObject& GetGameObject() const;
	std::shared_ptr<GameObject> gameObject;
	std::string name;
};

Component::Component(const std::string& name, const std::shared_ptr<GameObject>& gameObject)
	: name(name)
	, gameObject(gameObject)
{
	if (gameObject == nullptr) {
		//Paste hierarchy search here
	}
}

Component::Component(std::string&& name, GameObject&& gameObject) noexcept
	: name(std::move(name))
	, gameObject(&gameObject)
{}

Component::Component(Component&& component) noexcept
	: name(std::move(component.name))
	, gameObject(component.gameObject)
{}

Component::Component(const Component& component)
	: name(component.name)
	, gameObject(component.gameObject)
{}

Component::~Component()
{
	gameObject = nullptr;
}

GameObject& Component::GetGameObject() const
{
	return *gameObject;
}

struct ComponentView {
	ComponentView(void* Data) : Data(Data) {}
	~ComponentView() { delete Data; }
	template<class ComponentType>
	ComponentType* getComponentFromView() {
		return reinterpret_cast<ComponentType*>(Data);
	}
	std::string type;
private:
	void* Data;
};
#endif //COMPONENT