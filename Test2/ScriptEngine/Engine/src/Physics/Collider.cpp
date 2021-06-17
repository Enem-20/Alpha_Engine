#include "Collider.h"


void Physics::Collider::Update(glm::vec2 leftBottom, glm::vec2 rightTop)
{
	aabb.leftBottom = leftBottom;
	aabb.rightTop = rightTop;
}

bool Physics::Collider::CheckIntersect(const glm::dvec2& point)
{
	return ((point.x <= aabb.rightTop.x) && (point.x >= aabb.leftBottom.x) && (point.y <= aabb.rightTop.y) && (point.y >= aabb.leftBottom.y));
}