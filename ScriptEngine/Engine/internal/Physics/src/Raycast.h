#pragma once

#include "reactphysics3d/reactphysics3d.h"

#include <sol/sol.hpp>
#include <glm/glm.hpp>

#include <functional>
#include <unordered_set>
#include <limits>

class Collider2D;

class Raycast : public reactphysics3d::RaycastCallback{
public:
	Raycast();
	std::shared_ptr<Collider2D> closestBodyHit(const glm::vec3& start, const glm::vec3& end);

	virtual reactphysics3d::decimal notifyRaycastHit(const reactphysics3d::RaycastInfo& info);
private:
	std::shared_ptr<Collider2D> getCurrentCollider();

	std::shared_ptr<reactphysics3d::Ray> ray;
	float currentHitFraction = 0.0f;
	std::string currentColliderName = "";
	reactphysics3d::Vector3 currentPosition;
};