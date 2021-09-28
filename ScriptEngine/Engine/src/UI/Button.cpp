#include "Button.h"

#include <imgui/imgui.h>

#include "../Components/Component.h"
#include "../Input/Input.h"
#include "WindowManager.h"

namespace UI
{
	Button::Button(std::string name, std::shared_ptr<GameObject> gameObject) 
		: UIelement(name, gameObject)
	{
		state = States::Idle;
		if(name == ""){++ID;this->name = "someUI" + std::to_string(ID);}
			
		//ImGui::Begin(name.c_str());
		//if (ImGui::Button(name.c_str()))
		//	executeOnClicks();
		//ImGui::End();
		
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
		
		if(ImGui::Begin(name.c_str()))
			if (ImGui::Button(name.c_str()))
				executeOnClicks();

		ImGui::End();
	}

	void Button::FixedUpdate()
	{

	}

	Button::~Button()
	{
		//bool f = false;
		//if(ImGui::Begin(name.c_str(), &f))
		//	ImGui::End();
	}

	void Button::translate(const glm::vec2& newPos)
	{
		ImGui::Begin(name.c_str());
		ImGui::Button(name.c_str());
		ImGui::SetWindowPos({ GetGameObject().transform->position.x, (GetGameObject().transform->position.y - WindowManager::CurrentWindow->size.y) * -1});
		ImGui::End();
	}
}