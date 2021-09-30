#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "../Renderer/Renderer.h"


class Casts
{
public:
	static glm::vec3 CellToScreen(const glm::ivec2& ivec2, const glm::ivec2& cellSize)
	{
		glm::vec3 res(0.f);

		float scaleX = RenderEngine::Renderer::ViewportSize.x / cellSize.x;
		res.x = ivec2.x * scaleX;
		//res.x = std::max(res.x, (float)((RenderEngine::Renderer::ViewportSize.x - RenderEngine::Renderer::ViewportOffset.x) / cellSize.x));

		float scaleY = RenderEngine::Renderer::ViewportSize.y / cellSize.y;
		res.y = ivec2.y * scaleY;
		//res.y = std::max(res.y, (float)((RenderEngine::Renderer::ViewportSize.y - RenderEngine::Renderer::ViewportOffset.y) / cellSize.y));

		return res;
	}
};
