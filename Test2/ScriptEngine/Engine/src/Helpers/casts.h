#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

#include "vector3.h"
#include "mat3.h"

namespace Helpers
{
	static glm::vec3 toGLM_vec3(vector3& vec)
	{
		return glm::vec3(vec.x, vec.y, vec.z);
	}

	static glm::vec2 toGLM_vec2(vector2& vec)
	{
		return glm::vec2(vec.x, vec.y);
	}

	static glm::ivec2 toGLM_ivec2(vector2& vec)
	{
		return glm::ivec2(static_cast<int>(vec.x), static_cast<int>(vec.y));
	}

	static glm::ivec3 toGLM_ivec3(vector3& vec)
	{
		return glm::ivec3(static_cast<int>(vec.x), static_cast<int>(vec.y), static_cast<int>(vec.z));
	}

	static glm::mat3 toGLM_mat3(mat3& mat)
	{
		for (size_t i = 0; i < 3; ++i)
		{

		}
	}
}