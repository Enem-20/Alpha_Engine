#pragma once

#include "Component.h"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <memory>

#define OGL


class DLLEXPORT Transform : public Component
{
public:
	Transform(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);
#ifdef OGL
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
#endif // OGL
};
