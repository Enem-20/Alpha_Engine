#include "Transform.h"

#include "../../src/GameTypes/GameObject.h"

Transform::Transform(std::string name, std::shared_ptr<GameObject> gameObject)
	: position(std::make_shared<glm::vec3>(0.f))
	, rotation(std::make_shared<glm::vec3>(0.f))
	, scale(std::make_shared<glm::vec3>(1.f))
	, model(glm::mat4(1.f))
	, Component(name, gameObject)
{
	transform();
}
Transform::Transform(Transform&& transform) noexcept
	: position(std::move(transform.position))
	, rotation(std::move(transform.rotation))
	, scale(std::move(transform.scale))
	, model(std::move(transform.model))
	, Component(std::move(transform.name), std::move(transform.gameObject.lock()))
{}
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string name, std::shared_ptr<GameObject> gameObject)
	: position(std::make_shared<glm::vec3>(position))
	, rotation(std::make_shared<glm::vec3>(rotation))
	, scale(std::make_shared<glm::vec3>(scale))
	, Component(name, gameObject)
{
	transform();
}

Transform::Transform(const Transform& _transform)
	: position(_transform.position)
	, rotation(_transform.rotation)
	, scale(_transform.scale)
	, model(_transform.model)
	, Component(_transform.name, _transform.gameObject.lock())
{}

void Transform::Teleport(const glm::vec3& position)
{
	*(this->position) = position;

	transform();
}

void Transform::Translate(const glm::vec3& position)
{
	*(this->position) += position;

	transform();
}

void Transform::Rotate(const glm::vec3& rotation)
{
	*(this->rotation) += rotation;

	transform();
}

void Transform::Scale(const glm::vec3& scale)
{
	*(this->scale) += scale;

	transform();
}

void Transform::transform()
{
	model = glm::mat4(1.f);
	glm::mat4 same = glm::mat4(1.f);


	model = glm::rotate(model, glm::radians(rotation->x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation->y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation->z), glm::vec3(0, 0, 1));
	//position.z *= -1;
	model = glm::translate(model, *position);
	model = glm::scale(model, *scale);
}

const glm::mat4& Transform::GetModel() const
{
	return model;
}

glm::vec2 Transform::GetVec2Position() { return *position; }

glm::vec3 Transform::GetPosition() const
{
	return *position;
}
glm::vec3 Transform::GetRotation() const
{
	return *rotation;
}
glm::vec3 Transform::GetScale() const
{
	return *scale;
}

reactphysics3d::Transform Transform::ToPhysicsTransform() {
	auto physicsTransform = reactphysics3d::Transform(FromGLMToPhysicsVector3(*position), FromGLMToPhysicsQuaternion(*rotation));
	physicsTransform.setPosition(reactphysics3d::Vector3(physicsTransform.getPosition().x, physicsTransform.getPosition().y * -1, physicsTransform.getPosition().z));
	return physicsTransform;
}

std::shared_ptr<Transform> Transform::ToTransformFromPhysicsTransform(reactphysics3d::Transform physicsTransform, glm::vec3 scale) {
	auto EngineTransform = std::make_shared<Transform>(FromPhysicsVector3ToGLM(physicsTransform.getPosition()), FromPhysicsQuaternionToGLM(physicsTransform.getOrientation()), scale);
	EngineTransform->position->y *= -1;
	return EngineTransform;
}

reactphysics3d::Vector3 Transform::FromGLMToPhysicsVector3(const glm::vec3& vec) {
	return reactphysics3d::Vector3(vec.x, vec.y, vec.z);
}

glm::vec3 Transform::FromPhysicsVector3ToGLM(const reactphysics3d::Vector3& vec) {
	return glm::vec3(vec.x, vec.y, vec.z);
}

reactphysics3d::Quaternion Transform::FromGLMToPhysicsQuaternion(const glm::vec3& orientation) {
	glm::vec3 radiansRotation = glm::radians(orientation);
	return reactphysics3d::Quaternion::fromEulerAngles(reactphysics3d::Vector3(radiansRotation.x, radiansRotation.y, radiansRotation.z));
}

glm::vec3 Transform::FromPhysicsQuaternionToGLM(const reactphysics3d::Quaternion& orientation) {
	reactphysics3d::Vector3 physicsVector3;
	float angle;
	
	orientation.getRotationAngleAxis(angle, physicsVector3);

	reactphysics3d::Vector3 result = physicsVector3 * angle;

	return glm::vec3(result.x, result.y, result.z);
}