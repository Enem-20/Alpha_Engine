#include "vector3.h"

namespace Helpers
{
	vector3& vector3::operator+=(const vector3& _vector2)
	{
		this->x += _vector2.x;
		this->y += _vector2.y;
		this->z += _vector2.z;
		return vector3(*this);
	}

	vector3& vector3::operator-=(const vector3& _vector2)
	{
		this->x -= _vector2.x;
		this->y -= _vector2.y;
		this->z -= _vector2.z;
		return vector3(*this);
	}

	vector3& vector3::operator*=(const float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		this->z *= scalar;
		return vector3(*this);
	}

	vector3& vector3::operator=(const vector3& _vector2) noexcept
	{
		this->x = _vector2.x;
		this->y = _vector2.y;
		this->z = _vector2.z;
		return vector3(*this);
	}
}