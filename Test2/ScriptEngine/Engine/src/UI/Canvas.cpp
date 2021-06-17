#include "Canvas.h"

#include "../Input/Input.h"

namespace UI
{
	std::shared_ptr<GameObject> Canvas::WhatClicked()
	{
		for (auto el : UIelements)
		{
			return std::make_shared<GameObject>(el); //Бред, заменить
		}
	}
}