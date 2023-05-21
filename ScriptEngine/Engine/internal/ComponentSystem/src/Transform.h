#pragma once

#ifndef TRANSFORM
#define TRANSFORM

#include "Component.h"

#include <reactphysics3d/reactphysics3d.h>

#include <glm/gtc/matrix_transform.hpp>

#include <glm/glm.hpp>

#include <string>
#include <memory>

class GameObject;

class Transform : public Component
{
public:
	Transform(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);
	Transform(Transform&& transform) noexcept;
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);

	Transform(const Transform& _transform);

	~Transform() {
		gameObject.reset();
	}

	void Teleport(const glm::vec3& position);
	void Translate(const glm::vec3& position);
	void Rotate(const glm::vec3& rotation);
	void Scale(const glm::vec3& scale);
	void transform();
	const glm::mat4& GetModel() const;

	void Awake() override{}
	void Start() override {}
	void Update(uint32_t currentImage) override {}
	void FixedUpdate() override {}
	void LastUpdate() override {}

	glm::vec2 GetVec2Position();
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;

	reactphysics3d::Transform ToPhysicsTransform();
	static reactphysics3d::Vector3 FromGLMToPhysicsVector3(const glm::vec3& vec);
	static reactphysics3d::Quaternion FromGLMToPhysicsQuaternion(const glm::vec3& orientation);

	GENERATETYPE(Transform)
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
protected:
	glm::mat4 model;
};

#endif //!TRANSFORM