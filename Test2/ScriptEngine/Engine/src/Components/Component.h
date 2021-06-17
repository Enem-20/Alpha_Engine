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

		std::string name;
		std::shared_ptr<GameObject> gameObject;
	protected:

	};
}