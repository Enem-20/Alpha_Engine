#pragma once

#include <memory>

namespace Helpers
{
	class vector2
	{
	public:
		vector2(float x, float y)
			: x(x)
			, y(y)
		{}
		float x, y;

		std::shared_ptr<vector2> operator+(std::shared_ptr<vector2> _vector2)
		{
			return std::make_shared<vector2>(this->x + _vector2->x, this->y + _vector2->y);
		}

		std::shared_ptr<vector2> operator-(std::shared_ptr<vector2> _vector2)
		{
			return std::make_shared<vector2>(this->x - _vector2->x, this->y - _vector2->y);
		}

		std::shared_ptr<vector2> operator*=(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;

		}
		std::shared_ptr<vector2> operator*=(const std::shared_ptr<vector2> v)
		{
			this->x *= v->x;
			this->y *= v->y;

			return *this;
		}
	};
}