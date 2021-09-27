#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

#include "vector3.h"
#include "mat3.h"
#include "../Renderer/Renderer.h"

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

class Casts
{
public:
	static glm::vec3 CellToScreen(const glm::ivec2& ivec2)
	{
		glm::vec3 res(0.f);

		float scaleX = (RenderEngine::Renderer::ViewportSize.x - RenderEngine::Renderer::ViewportSize.x / 8) / 7;
		res.x = ivec2.x * scaleX;

		float scaleY = (RenderEngine::Renderer::ViewportSize.y - RenderEngine::Renderer::ViewportSize.y / 8) / 7;
		res.y = ivec2.y * scaleY;
		//float board_pos_x = ivec2.x - RenderEngine::Renderer::ViewportOffset.x;
		//float board_pos_y = ivec2.y - RenderEngine::Renderer::ViewportOffset.y;

		//if (board_pos_x >= 0 && board_pos_x <= RenderEngine::Renderer::ViewportSize.x && board_pos_y >= 0 && board_pos_y <= RenderEngine::Renderer::ViewportSize.x)
		//{
		//	unsigned int cellSize = ((unsigned int)RenderEngine::Renderer::ViewportSize.x << 3);
		//	res.x = board_pos_x / cellSize;
		//	res.y = board_pos_y / cellSize;
		//	//std::cout << "cell (" << cell_x << ", " << cell_y << ")" << std::endl;
		//}

		return res;
	}
};