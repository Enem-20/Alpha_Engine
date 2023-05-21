#include "Panel.h"

#include "../../src/Resources/ResourceManager.h"
#include "../../src/GameTypes/GameObject.h"
#include "../../ComponentSystem/src/Transform.h"
#include "../../Renderer/src/WindowManager.h"

#include <imgui/imgui.h>

#include <unordered_map>
#include <iostream>

Panel::Panel(const std::string& name, std::shared_ptr<GameObject> gameObject)
	: UIelement(name, gameObject)
{
	ResourceManager::addResource<Panel>(this);
}

Panel::~Panel() {
	ResourceManager::removeResource<Panel>(name);
}

void Panel::Awake() {

}
void Panel::Start() {

}
void Panel::Update(uint32_t currentImage) {
	if (ImGui::Begin(name.c_str()))
		for (auto ui : uis) {
			ui.second->Update(currentImage);
		}

	ImGui::End();
}
void Panel::FixedUpdate() {

}
void Panel::LastUpdate() {

}

void Panel::translate(const glm::vec2& newPos) {
	ImGui::Begin(name.c_str());
	ImGui::SetWindowPos({ GetGameObject()->getComponent<Transform>(name)->position.x, (GetGameObject()->getComponent<Transform>(name)->position.y - WindowManager::CurrentWindow->size.y) * -1 });
	ImGui::End();
}

void Panel::addChild(std::shared_ptr<UIelement> ui) {
	if (uis.contains(ui->name)) {
		std::cout << ui->name + " alreay exists" << '\n';
		return;
	}

	uis.emplace(ui->name, ui);
}