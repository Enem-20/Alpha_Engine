#pragma once

#ifndef PANEL
#define PANEL

#include "../../src/Resources/ResourceManager.h"
#include "../../src/Resources/ResourceBase.h"
//#include "Button.h"
#include "UIelement.h"

#include <memory>
#include <string>
#include <unordered_map>

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

	template<class UIelementType>
	void addChild(std::shared_ptr<UIelementType> ui);

	template<class UIelementType>
	void removeChild(const std::string& name);

	template<class UIelementType>
	std::shared_ptr<UIelementType> getChild(const std::string& name);

	template<class UIelementType>
	std::unordered_map<std::string, UIelementView>* getChildrenWithType();

	GENERATETYPE(Panel)
private:
	std::unordered_map<std::string, std::shared_ptr<UIelement>> uis;

	std::unordered_map<std::string, std::unordered_map<std::string, UIelementView>> m_uis;
};

template<class UIelementType>
void Panel::addChild(std::shared_ptr<UIelementType> ui) {
	static_assert(std::is_base_of<UIelement, UIelementType>::value || std::is_same<UIelement, UIelementType>::value, "UIelementType must inherit from UIelement or be a UIelement");
	ui->parent = ResourceManager::getResource<Panel>(this->name);

	auto uiElementsByType = m_uis.find(UIelementType::type);
	if (uiElementsByType != m_uis.end()) {
		uiElementsByType->second.emplace(ui->name, UIelementView{ std::reinterpret_pointer_cast<void>(ui) });
	}
	else {
		m_uis[UIelementType::type].emplace(ui->name, UIelementView{ std::reinterpret_pointer_cast<void>(ui) });
	}
}

template<class UIelementType>
void Panel::removeChild(const std::string& name) {
	static_assert(std::is_base_of<UIelement, UIelementType>::value || std::is_same<UIelement, UIelementType>::value, "UIelementType must inherit from UIelement or be a UIelement");
	size_t currentIndex = 0;

	auto uisByType = m_uis.find(UIelementType::type);

	if (uisByType != m_uis.end())
		uisByType->second.erase(name);
}

template<class UIelementType>
std::shared_ptr<UIelementType> Panel::getChild(const std::string& name) {
	static_assert(std::is_base_of<UIelement, UIelementType>::value || std::is_same<UIelement, UIelementType>::value, "UIelementType must inherit from UIelement or be a UIelement");
	auto uisByType = m_uis.find(UIelementType::type);

	if (uisByType != m_uis.end()) {
		auto ui = uisByType->second.find(name);

		if (ui != uisByType->second.end()) {
			return ui->second.getUIFromView<UIelementType>();
		}
	}

	return nullptr;
}

template<class UIelementType>
std::unordered_map<std::string, UIelementView>* Panel::getChildrenWithType() {
	static_assert(std::is_base_of<UIelement, UIelementType>::value || std::is_same<UIelement, UIelementType>::value, "UIelementType must inherit from UIelement or be a UIelement");

	auto uisByType = m_uis.find(UIelementType::type);

	if (uisByType != m_uis.end()) {
		return &uisByType->second;
	}

	return nullptr;
}

#endif // !PANEL
