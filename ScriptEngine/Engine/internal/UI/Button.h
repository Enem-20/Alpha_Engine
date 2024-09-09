#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include "API/ExportPropety.h"

#include "UIelement.h"

#include <glm/glm.hpp>

#include <string>
#include <memory>

class GameObject;

class DLLEXPORT Button : public UIelement
{
public:
	Button(const std::string& name, std::shared_ptr<GameObject> gameObject = nullptr);
	~Button();

	enum class States { Idle, Down, Stay, Up };

	void Awake() override;
	void Start() override;
	void Update(uint32_t currentFrame) override;
	void FixedUpdate() override;
	void LastUpdate() override;

	virtual void translate(const glm::vec2& newPos) override;

	GENERATETYPE(Button)
protected:
	States state;
};

#endif //BUTTON