#pragma once

#ifndef TRANSFORM
#define TRANSFORM

#include "Component.h"

#include <glm/gtc/matrix_transform.hpp>

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <memory>

class Transform : public Component
{
public:
	Transform(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);
	Transform(Transform&& transform) noexcept;
	Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);

	Transform(const Transform& _transform);

	void Teleport(const glm::vec3& position);
	void Translate(const glm::vec3& position);
	void Rotate(const glm::vec3& rotation);
	void Scale(const glm::vec3& scale);
	void transform();
	const glm::mat4& GetModel() const;

	glm::vec2 GetVec2Position();
	glm::vec3 GetPosition() const;
	glm::vec3 GetRotation() const;
	glm::vec3 GetScale() const;
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
protected:
	glm::mat4 model;
};


Transform::Transform(std::string name, std::shared_ptr<GameObject> gameObject)
	: position(glm::vec3(0.f))
	, rotation(glm::vec3(0.f))
	, scale(glm::vec3(0.f))
	, model(glm::mat4(1.f))
	, Component(name, gameObject)
{}
Transform::Transform(Transform&& transform) noexcept
	: position(std::move(transform.position))
	, rotation(std::move(transform.rotation))
	, scale(std::move(transform.scale))
	, model(std::move(transform.model))
	, Component(std::move(transform.name), transform.gameObject)
{}
Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string name, std::shared_ptr<GameObject> gameObject)
	: position(position)
	, rotation(rotation)
	, scale(scale)
	, Component(name, gameObject)
{
	Translate(glm::vec3(0.f));
	Rotate(glm::vec3(0.f));
	Scale(scale);
}

Transform::Transform(const Transform& _transform)
	: position(_transform.position)
	, rotation(_transform.rotation)
	, scale(_transform.scale)
	, model(_transform.model)
	, Component(_transform.name, _transform.gameObject)
{}

void Transform::Teleport(const glm::vec3& position)
{
	this->position = position;

	transform();
}

void Transform::Translate(const glm::vec3& position)
{
	this->position += position;

	transform();
}

void Transform::Rotate(const glm::vec3& rotation)
{
	this->rotation += rotation;

	transform();
}

void Transform::Scale(const glm::vec3& scale)
{
	this->scale += scale;

	transform();
}

void Transform::transform()
{
	model = glm::mat4(1.f);
	glm::mat4 same = glm::mat4(1.f);


	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
	model = glm::translate(model, position);
	model = glm::scale(model, scale);
}

const glm::mat4& Transform::GetModel() const
{
	return model;
}

glm::vec2 Transform::GetVec2Position() { return position; }

glm::vec3 Transform::GetPosition() const
{
	return position;
}
glm::vec3 Transform::GetRotation() const
{
	return rotation;
}
glm::vec3 Transform::GetScale() const
{
	return scale;
}


#endif //!TRANSFORM