#pragma once

#include "UIelement.h"

#include <glm/mat4x4.hpp>

namespace UI
{
	class Button : public UIelement
	{
	public:
		~Button();

		Button(std::string name = "", std::shared_ptr<GameObject> gameObject = nullptr);

		enum class States { Idle, Down, Stay, Up };

		void Awake() override;
		void Start() override;
		void Update() override;
		void FixedUpdate() override;

		void translate(const glm::vec2& newPos) override;

	protected:
		States state;
	};
}