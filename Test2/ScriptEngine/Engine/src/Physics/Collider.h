#pragma once

#include<glm/vec2.hpp>

namespace Physics
{
	class Collider
	{
	public:
		Collider()
		{
		}

		Collider(glm::vec2 leftBottom, glm::vec2 rightTop)
		{
			aabb.leftBottom = leftBottom;
			aabb.rightTop = rightTop;
		}

		struct AABB
		{
			AABB()
			{
				leftBottom = glm::vec2(0.f);
				rightTop = glm::vec2(0.f);
			}
			AABB(glm::vec2 leftBottom, glm::vec2 rightTop)
				: leftBottom(leftBottom)
				, rightTop(rightTop)
			{}

			glm::vec2 leftBottom;
			glm::vec2 rightTop;
		};

		bool CheckIntersect(const glm::dvec2& point);

		void Update(glm::vec2 leftBottom, glm::vec2 rightTop);
	private:
		AABB aabb;
	};
}