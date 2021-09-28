#include "vector2.h"

namespace Helpers
{
	vector2& vector2::operator+=(const vector2& _vector2)
	{
		this->x += _vector2.x;
		this->y += _vector2.y;
		return vector2(*this);
	}

	vector2& vector2::operator-=(const vector2& _vector2)
	{
		this->x -= _vector2.x;
		this->y -= _vector2.y;
		return vector2(*this);
	}

	vector2& vector2::operator*=(const float scalar)
	{
		this->x *= scalar;
		this->y *= scalar;
		return vector2(*this);
	}

	vector2& vector2::operator*=(const vector2& _vector2)
	{
		this->x *= _vector2.x;
		this->y *= _vector2.y;

		return vector2(*this);
	}

	vector2& vector2::operator=(const vector2& _vector2) noexcept
	{
		this->x = _vector2.x;
		this->y = _vector2.y;
		return vector2(*this);
	}
}