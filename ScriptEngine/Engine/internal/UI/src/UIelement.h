#pragma once

#ifndef UIELEMENT
#define UIELEMENT

#include "../../ComponentSystem/src/Component.h"

#include <sol/sol.hpp>
#include <glm/vec2.hpp>

#include <list>
#include <memory>
#include <string>

class GameObject;

class UIelement : public Component
{
public:
	UIelement(const std::string& name, std::shared_ptr<GameObject> gameObject);
	UIelement(const UIelement& uiElement);
	UIelement(UIelement&& uiElement) noexcept;

	virtual void AddListener(const sol::protected_function& func);

	virtual void executeOnClicks();

	virtual void Awake() = 0;
	virtual void Start() = 0;
	virtual void Update(uint32_t currentImage) = 0;
	virtual void FixedUpdate() = 0;
	virtual void LastUpdate() = 0;

	//void setParamCollider();
	//virtual void OnExecute() = 0;

	virtual void translate(const glm::vec2& newPos) = 0;
	//virtual void render(glm::mat4 model) = 0;

	//std::shared_ptr<Physics::Collider> collider;
protected:
	std::list<sol::protected_function> elements;
	static size_t ID;

#if defined(OGL) || defined(GLFW_INCLUDE_VULKAN)
	glm::vec2 position;
#endif
};
#endif //UIELEMENT