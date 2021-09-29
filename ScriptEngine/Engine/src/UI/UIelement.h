#pragma once

#include "../Components/Component.h"

#include <sol/sol.hpp>
#include <glm/vec2.hpp>

#include <list>
#include<memory>

class GameObject;

namespace UI
{
	class UIelement : public Components::Component
	{
	public:
		glm::mat4 model;

		//UIelement(UIelement&& ui) noexcept;
		UIelement(std::string name, std::shared_ptr<GameObject> gameObject)
			: Components::Component(name, gameObject)
		{}

		virtual void AddListener(const sol::protected_function& func);

		void executeOnClicks();
		//void setParamCollider();
		//virtual void OnExecute() = 0;

		virtual void Awake() = 0;
		virtual void Start() = 0;
		virtual void Update() = 0;  
		virtual void FixedUpdate() = 0;

		virtual void translate(const glm::vec2& newPos) = 0;
		//virtual void render(glm::mat4 model) = 0;

		//std::shared_ptr<Physics::Collider> collider;
	protected:		

		std::list<sol::protected_function> elements;
		static size_t ID;
	};
}