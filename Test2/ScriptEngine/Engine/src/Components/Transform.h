#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <memory>

#define OGL

namespace Components
{
	class Component;

	class Transform : public Component
	{
	public:
		Transform(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr)
			: position(glm::vec3(0.f))
			, rotation(glm::vec3(0.f))
			, scale(glm::vec3(0.f))
			, model(glm::mat4(1.f))
			, Component(name, gameObject)
		{}	
#ifdef OGL
		Transform(Transform&& transform) noexcept
			: position(std::move(transform.position))
			, rotation(std::move(transform.rotation))
			, scale(std::move(transform.scale))
			, model(std::move(transform.model))
			//, Component(std::move(transform.name), std::move(*transform.gameObject))
		{}
		Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr)
			: position(position)
			, rotation(rotation)
			, scale(scale)
			, Component(name, gameObject)
		{
			Translate(glm::vec3(0.f));
			Rotate(glm::vec3(0.f));
			Scale(scale);
		}

		Transform(const Transform& _transform)
			: position(_transform.position)
			, rotation(_transform.rotation)
			, scale(_transform.scale)
			, model(_transform.model)
			, Component(_transform.name, _transform.gameObject)
		{}

		void Translate(const glm::vec3& position);
		void Rotate(const glm::vec3& rotation);
		void Scale(const glm::vec3& scale);
		void transform();
		const glm::mat4& GetModel() const
		{
			return model;
		}
	public:
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	protected:
		glm::mat4 model;
#endif // OGL
	};
}