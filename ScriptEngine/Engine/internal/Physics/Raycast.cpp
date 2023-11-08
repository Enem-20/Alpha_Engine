#include "Raycast.h"

#include "Resources/ResourceManager.h"

#include "ComponentSystem/Collider2D.h"
#include "ComponentSystem/Transform.h"
#include "Physics.h"

#include <cmath>

Raycast::Raycast()
	
{}

std::shared_ptr<Collider2D> Raycast::closestBodyHit(const glm::vec3& start, const glm::vec3& end) {
	ray = std::make_shared<reactphysics3d::Ray>(Transform::FromGLMToPhysicsVector3(start), Transform::FromGLMToPhysicsVector3(end));

	auto transform = reactphysics3d::Transform(Transform::FromGLMToPhysicsVector3(start), reactphysics3d::Quaternion::identity());
	auto world = Physics::getWorld();
	world->raycast(*ray, this);

	return getCurrentCollider();
}

reactphysics3d::decimal Raycast::notifyRaycastHit(const reactphysics3d::RaycastInfo& info) {

	std::cout << "Hit point : " << '(' <<
		info.worldPoint.x << ',' <<
		info.worldPoint.y << ',' <<
		info.worldPoint.z << ')' <<
		std::endl;

		auto userData = info.body->getUserData();
		if (userData)
			currentColliderName = *reinterpret_cast<std::string*>(info.body->getUserData());
		else
			currentColliderName = "";

		currentPosition = info.worldPoint;

	currentHitFraction = info.hitFraction;
	

	// Return a fraction of 1.0 to gather all hits 
	return reactphysics3d::decimal(1.0f);
}

std::shared_ptr<Collider2D> Raycast::getCurrentCollider() {
	return ResourceManager::getResource<Collider2D>(currentColliderName);
}