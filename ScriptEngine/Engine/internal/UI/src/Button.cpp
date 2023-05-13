#include "Button.h"

#include "../../../src/GameTypes/GameObject.h"


#include "../../Renderer/src/WindowManager.h"
#include "../../Renderer/src/Window.h"
#include "../../ComponentSystem/src/Transform.h"

#include "../../src/Resources/ResourceManager.h"


#include <imgui/imgui.h>

#include <unordered_map>

Button::Button(const std::string& name, std::shared_ptr<GameObject> gameObject)
	: UIelement(name, gameObject)
{
	state = States::Idle;
	if (name == "") { this->name = "someUI" + std::to_string(ID); }

	//ResourceManager::addResource<Button>(this);
}

void Button::Awake()
{

}

void Button::Start()
{
	ImGui::Begin(name.c_str());
	ImGui::Button(name.c_str());
	ImGui::SetWindowPos({ GetGameObject()->transform->position.x, (GetGameObject()->transform->position.y - WindowManager::CurrentWindow->size.y) * -1 });
	ImGui::End();
}

void Button::Update()
{
	if (ImGui::Begin(name.c_str()))
		if (ImGui::Button(name.c_str()))
			executeOnClicks();

	ImGui::End();
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
	ImGui::SetWindowPos({ GetGameObject()->transform->position.x, (GetGameObject()->transform->position.y - WindowManager::CurrentWindow->size.y) * -1 });
	ImGui::End();
}