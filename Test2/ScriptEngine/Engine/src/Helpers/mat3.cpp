#include "mat3.h"

namespace Helpers
{
	mat3::mat3(mat3&& _mat2)noexcept
	{
		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				mat[i][j] = _mat2.mat[i][j];
			}
		}
	}

	void mat3::transpose()
	{
		std::array<std::array<float, 3>, 3> Bufmat;

		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				Bufmat[i][j] = mat[i][j];
			}
		}

		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				mat[i][j] = Bufmat[j][i];
			}
		}
	}

	mat3& mat3::operator*=(float same)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				mat[i][j] *= same;
			}
		}
		return *this;
	}
	mat3& mat3::operator+=(mat3& _mat2)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				mat[i][j] += _mat2.mat[i][j];
			}
		}

		return *this;
	}
	mat3& mat3::operator-=(mat3& _mat2)
	{
		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				mat[i][j] -= _mat2.mat[i][j];
			}
		}

		return *this;
	}
	mat3& mat3::operator*=(mat3& _mat2)
	{
		float** c = new float* [3];
		for (int i = 0; i < 3; i++)
		{
			c[i] = new float[3];
			for (int j = 0; j < 3; j++)
			{
				c[i][j] = 0;
				for (int k = 0; k < 3; k++)
					c[i][j] += mat[i][k] * _mat2.mat[k][j];
			}
		}

		for (size_t i = 0; i < 3; ++i)
		{
			for (size_t j = 0; j < 3; ++j)
			{
				mat[i][j] = c[i][j];
			}
		}

		return *this;
	}
}