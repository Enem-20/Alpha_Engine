#pragma once

#include "Hierarchy.h"

class Scene
{
public:
	static Scene* GetInstance();
	
	static std::string name;
private:	
	Scene() = default;
	inline static Scene* scene;
};