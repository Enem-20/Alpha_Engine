#pragma once

#include <string>
#include <memory>

class GameObject;

namespace Components
{
	class Component
	{
	public:
		Component(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr)
			: name(name)
			, gameObject(gameObject)
		{}
		Component(std::string&& name, GameObject&& gameObject) noexcept
			: name(std::move(name))
			, gameObject(std::move(&gameObject))
		{}

		~Component()
		{
			gameObject = nullptr;
		}
		//Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject)
		//	: name(name)
		//	, gameObject(gameObject)
		//{}
		GameObject& GetGameObject() const;

		std::string name;
		std::shared_ptr<GameObject> gameObject;
	protected:

	};
}