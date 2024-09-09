#pragma once

#ifndef PHYSICS_H
#define PHYSICS_H

#include "reactphysics3d/reactphysics3d.h"

class Physics {
public:
	static reactphysics3d::PhysicsWorld* getWorld();
	static reactphysics3d::PhysicsCommon& getCommon();
private:
	static reactphysics3d::PhysicsCommon physicsCommon;
	static reactphysics3d::PhysicsWorld* world;
};

#endif