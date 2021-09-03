#pragma once

#include "UIelement.h"

#include <glm/mat4x4.hpp>

namespace UI
{
	class Button : public UIelement
	{
	public:
		Button();

		Button(std::string name = "");

		enum class States { Idle, Down, Stay, Up };

		void render(glm::mat4 model)override
		{

		}

		void Update() override
		{
			switch (state)
			{
			case States::Idle:
				break;
			case States::Down:
				executeOnClicks();
				state = States::Idle;
				break;
			case States::Stay:
				break;
			case States::Up:
				break;
			}
		}

	protected:
		States state;
	};
}