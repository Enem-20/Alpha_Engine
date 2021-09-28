#pragma once 

#include "../Input/Input.h"

#include <sol/sol.hpp>

#include <list>
#include<memory>

class GameObject;

namespace UI
{
	class Canvas
	{
	public:
		static void render();
		std::shared_ptr<GameObject> WhatClicked();
	private:
		std::list<GameObject> UIelements;
	};
}