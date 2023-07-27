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

	shape = common.createBoxShape(reactphysics3d::Vector3(transform->scale->x, transform->scale->y, transform->scale->z));
	collisionBody = world->createCollisionBody(transform->ToPhysicsTransform());
	collisionBody->addCollider(shape, reactphysics3d::Transform(reactphysics3d::Vector3(0.0f, 0.0f, 0.0f), reactphysics3d::Quaternion::identity()));
	collisionBody->setUserData(toVoidPointer());

	ResourceManager::addResource<Collider2D>(this);
}

Collider2D::~Collider2D() {
	Physics::getWorld()->destroyCollisionBody(collisionBody);
}

void* Collider2D::toVoidPointer() {
	return reinterpret_cast<void*>(&name);
}

std::string* Collider2D::colliderNameFromVoidPointer(void* data) {
	return reinterpret_cast<std::string*>(data);
}

void Collider2D::Awake() {

}

void Collider2D::Start() {

}

void Collider2D::Update(uint32_t currentImage) {

}

void Collider2D::FixedUpdate() {

}

void Collider2D::LastUpdate() {

}

void Collider2D::SetTransform(std::shared_ptr<Transform> transform) {
	reactphysics3d::Transform tr = transform->ToPhysicsTransform();
	collisionBody->setTransform(tr);
}

std::shared_ptr<Transform> Collider2D::getTransform() {
	return Transform::ToTransformFromPhysicsTransform(collisionBody->getTransform(), Transform::FromPhysicsVector3ToGLM(shape->getHalfExtents()));
}