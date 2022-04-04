#pragma once

#include "../ExportPropety.h"

#include <string>
#include <memory>

class GameObject;


class DLLEXPORT Component
{
public:
	Component(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);
	Component(std::string&& name, GameObject&& gameObject) noexcept;

	~Component();
	//Component(std::string&& name, std::shared_ptr<GameObject>&& gameObject)
	//	: name(name)
	//	, gameObject(gameObject)
	//{}
	GameObject& GetGameObject() const;

	std::string name;
	std::shared_ptr<GameObject> gameObject;
};
