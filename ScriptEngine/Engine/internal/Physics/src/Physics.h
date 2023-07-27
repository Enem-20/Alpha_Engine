#pragma once

#include "reactphysics3d/reactphysics3d.h"

#ifndef PHYSICS
#define PHYSICS

class Physics {
public:
	static reactphysics3d::PhysicsWorld* getWorld();
	static reactphysics3d::PhysicsCommon& getCommon();
private:
	static reactphysics3d::PhysicsCommon physicsCommon;
	static reactphysics3d::PhysicsWorld* world;
};

#endif