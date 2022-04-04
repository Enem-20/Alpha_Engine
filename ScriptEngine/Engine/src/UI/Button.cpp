#include "Button.h"

#include <imgui/imgui.h>

#include "WindowManager.h"
#include "Window.h"
#include "../GameTypes/GameObject.h"
#include "../Components/Transform.h"

Button::Button(std::string name, std::shared_ptr<GameObject> gameObject)
	: UIelement(name, gameObject)
{
	state = States::Idle;
	if (name == "") { ++ID; this->name = "someUI" + std::to_string(ID); }

	WindowManager::CurrentWindow->AddUI(std::move(*this));
}

void Button::Awake()
{

}

void Button::Start()
{
	ImGui::Begin(name.c_str());
	ImGui::Button(name.c_str());
	ImGui::SetWindowPos({ GetGameObject().transform->position.x, (GetGameObject().transform->position.y - WindowManager::CurrentWindow->size.y) * -1 });
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

Button::~Button()
{
}

void Button::translate(const glm::vec2& newPos)
{
	ImGui::Begin(name.c_str());
	ImGui::Button(name.c_str());
	ImGui::SetWindowPos({ GetGameObject().transform->position.x, (GetGameObject().transform->position.y - WindowManager::CurrentWindow->size.y) * -1 });
	ImGui::End();
}
