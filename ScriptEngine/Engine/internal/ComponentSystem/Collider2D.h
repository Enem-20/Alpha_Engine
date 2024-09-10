#pragma once

#ifndef COLLIDER_2D_H
#define COLLIDER_2D_H

#include "API/ExportPropety.h"

#include "Component.h"

#include <glm/glm.hpp>

#include <string>
#include <memory>

class GameObject;
class Transform;

namespace reactphysics3d {
	class CollisionBody;

	class BoxShape;
};

class DLLEXPORT Collider2D : public Component {
public:
	Collider2D(const std::string& name, std::shared_ptr<Transform> transform = std::make_shared<Transform>(), std::shared_ptr<GameObject> gameObject = nullptr);
	~Collider2D();
	void* toVoidPointer();
	std::string* colliderNameFromVoidPointer(void* data);

	virtual void Awake();
	virtual void Start();
	virtual void Update(uint32_t currentFrame);
	virtual void FixedUpdate();
	virtual void LastUpdate();

	void SetTransform(std::shared_ptr<Transform> transform);

	std::shared_ptr<Transform> getTransform();

	GENERATETYPE(Collider2D)
private:
	reactphysics3d::BoxShape* shape;
	reactphysics3d::CollisionBody* collisionBody;
};

#endif