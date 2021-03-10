#pragma once

#include <array>
#include <memory>

namespace Helpers
{
	class mat3
	{
	public:
		mat3(mat3&& _mat2)noexcept;
		std::array<std::array<float, 3>, 3> mat;

		
		mat3& operator-=(mat3& _mat2);
		mat3& mat3::operator+=(mat3& _mat2);
		mat3& operator*=(float same);
		mat3& operator*=(mat3& _mat2);

		void transpose();
	};
}