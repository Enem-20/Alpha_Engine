#pragma once

#include "vector2.h"

namespace Helpers
{
	class vector3
	{
	public:
		vector3()
			: x(0)
			, y(0)
			, z(0)
		{}
		vector3(float x, float y, float z) 
			: x(x)
			, y(y)
			, z(z)
		{}
		vector3(const vector2& _vector2, float z)
			: x(_vector2.x)
			, y(_vector2.y)
			, z(z)
		{}
		float x,y,z;

		float GetX()
		{
			return x;
		}

		void SetX(float new_x)
		{
			x = new_x;
		}

		vector3& operator+=(const vector3& _vector2);
									
		vector3& operator-=(const vector3& _vector2);
									  
		vector3& operator*=(const float scalar);
									  
		vector3& operator*=(const vector3& _vector2);

		friend float operator*(const vector3& _vector, const vector3& _vector2)
		{
			return _vector.x * _vector2.x + _vector.y * _vector2.y + _vector.z * _vector2.z;
		}

		friend float operator^(const vector3& _vector, const vector3& _vector2)
		{
			return _vector.x * _vector2.y + _vector2.x * _vector.y;
		}

		vector3& operator=(const vector3& _vector2) noexcept;
	};
}