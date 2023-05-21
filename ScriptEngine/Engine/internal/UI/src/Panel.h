#pragma once

#ifndef PANEL
#define PANEL

#include "../../src/Resources/ResourceBase.h"
#include "UIelement.h"

#include <memory>
#include <string>

class GameObject;

class Panel : public UIelement {
public:
	Panel(const std::string& name = "", std::shared_ptr<GameObject> gameObject = nullptr);
	~Panel();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update(uint32_t currentImage) override;
	virtual void FixedUpdate() override;
	virtual void LastUpdate() override;

	virtual void translate(const glm::vec2& newPos) override;

	void addChild(std::shared_ptr<UIelement> ui);

	GENERATETYPE(Panel)
private:
	std::unordered_map<std::string, std::shared_ptr<UIelement>> uis;
};

#endif // !PANEL
