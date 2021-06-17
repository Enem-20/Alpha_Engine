#include "Button.h"

#include "../Input/Input.h"

namespace UI
{
	Button::Button() : UIelement()
	{
		state = States::Idle;
		++ID;
		Input::AddUI("someUI" + std::to_string(ID), std::make_shared<UI::Button>(*this));
	}

	Button::Button(std::string name) : UIelement()
	{
		state = States::Idle;
		this->name = name;
		++ID;
		Input::AddUI("someUI" + std::to_string(ID), std::make_shared<UI::Button>(*this));
	}
}