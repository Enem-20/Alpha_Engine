#pragma once

#include "GameObject.h"

class Desk : public GameObject
{
public:
	Desk();

	void render() override;
};