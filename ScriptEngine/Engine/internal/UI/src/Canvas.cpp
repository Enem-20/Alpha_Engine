#include "Canvas.h"

#include "../../internal/Physics/src/Physics.h"

Canvas::Canvas() {
	body = Physics::getWorld()->createCollisionBody(reactphysics3d::Transform(reactphysics3d::Vector3(0.0f, 0.0f, 0.0f), reactphysics3d::Quaternion::identity()));
}

reactphysics3d::CollisionBody* Canvas::getCollisionBody() {
	return body;
}