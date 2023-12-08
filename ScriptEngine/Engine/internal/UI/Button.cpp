#include "Button.h"

#include "GameTypes/GameObject.h"


#include "Renderer/src/WindowManager.h"
#include "Renderer/src/Window.h"
#include "ComponentSystem/Transform.h"

#include "Resources/ResourceManager.h"


#include <imgui/imgui.h>

#include <unordered_map>

Button::Button(const std::string& name, std::shared_ptr<GameObject> gameObject)
	: UIelement(name, gameObject)
{
	state = States::Idle;
	if (name == "") { this->name = "someUI" + std::to_string(ID); }
}

void Button::Awake()
{

}

void Button::Start()
{
	ImGui::Begin(name.c_str());
	ImGui::Button(name.c_str());
	ImGui::SetWindowPos({ GetGameObject()->getComponent<Transform>(name)->position->x, (GetGameObject()->getComponent<Transform>(name)->position->y - WindowManager::CurrentWindow->size.y) * -1 });
	ImGui::End();
}

void Button::Update(uint32_t currentFrame)
{
	if (ImGui::Button(name.c_str()))
			executeOnClicks();
}

void Button::FixedUpdate()
{

}

void Button::LastUpdate() {

}

Button::~Button()
{
}

void Button::translate(const glm::vec2& newPos)
{
	ImGui::Begin(name.c_str());
	ImGui::Button(name.c_str());
	ImGui::SetWindowPos({ GetGameObject()->getComponent<Transform>(name)->position->x, (GetGameObject()->getComponent<Transform>(name)->position->y - WindowManager::CurrentWindow->size.y) * -1 });
	ImGui::End();
}