#pragma once

#include <map>
#include <string>
#include "../Game/GObject.h"

class Hierarchy
{
public:
private:
	std::map<std::string, GObject> SceneObjects;
};