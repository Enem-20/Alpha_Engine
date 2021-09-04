#include "Transform.h"

#include "Component.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Components
{
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
}