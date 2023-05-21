#include "Physics.h"

reactphysics3d::PhysicsCommon Physics::physicsCommon;
reactphysics3d::PhysicsWorld* Physics::world = physicsCommon.createPhysicsWorld();


reactphysics3d::PhysicsWorld* Physics::getWorld() {
	return world;
}

reactphysics3d::PhysicsCommon& Physics::getCommon() {
	return physicsCommon;
}