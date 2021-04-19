#pragma once

#include "Resources/ResourceManager.h"
#include "GameTypes/Game.h"
#include "GameTypes/GameObject.h"
#include "GameTypes/Desk.h"
//#include <memory>

namespace Engine
{
	class EngineMain
	{
	public:
		static void Init(char** argv);
	private:
		static void FirstFrame();
	};
}