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
		vector2(const vector2& _vector2)
			: x(_vector2.x)
			, y(_vector2.y)
		{}

		float x, y;

		vector2& operator+=(const vector2& _vector2);

		vector2& operator-=(const vector2& _vector2);

		vector2& operator*=(const float scalar);

		vector2& operator*=(const vector2& _vector2);

		/*std::shared_ptr<vector2> operator^=(const std::shared_ptr<vector2> _vector2)
		{
			this->x *= _vector2->y;
			this->y *= _vector2->x;

			return std::make_shared<vector2>(*this);
		}*/

		friend float operator*(const vector2& _vector, const vector2& _vector2)
		{
			return _vector.x * _vector2.x + _vector.y * _vector2.y;
		}

		friend float operator^(const vector2& _vector, const vector2& _vector2)
		{
			return _vector.x * _vector2.y + _vector2.x * _vector.y;
		}

		vector2& operator=(const vector2& _vector2) noexcept;
	};
}