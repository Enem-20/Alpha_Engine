#include "Collider2D.h"

#include "../../src/Resources/ResourceManager.h"

#include "../../src/GameTypes/GameObject.h"
#include "Transform.h"

#include "../../Physics/src/Physics.h"

#include <reactphysics3d/reactphysics3d.h>

Collider2D::Collider2D(const std::string& name, std::shared_ptr<Transform> transform, std::shared_ptr<GameObject> gameObject)
	: Component(name, gameObject)
{
	auto& common = Physics::getCommon();
	auto world = Physics::getWorld();

	shape = common.createBoxShape(reactphysics3d::Vector3(transform->scale.x/(float)2, transform->scale.y/(float)2, transform->scale.z/(float)2));
	collisionBody = world->createCollisionBody(transform->ToPhysicsTransform());
	collisionBody->addCollider(shape, transform->ToPhysicsTransform());
	collisionBody->setUserData(toVoidPointer());

	ResourceManager::addResource<Collider2D>(this);
}

Collider2D::~Collider2D() {
	ResourceManager::removeResource<Collider2D>(name);
}

void* Collider2D::toVoidPointer() {
	return reinterpret_cast<void*>(&name);
}

std::string* Collider2D::colliderNameFromVoidPointer(void* data) {
	return reinterpret_cast<std::string*>(data);
}