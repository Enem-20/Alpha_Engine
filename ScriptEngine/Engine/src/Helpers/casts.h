#pragma once

#include "../ExportPropety.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "../Renderer/Renderer.h"


class DLLEXPORT Casts
{
public:
	static glm::vec3 CellToScreen(const glm::ivec2& ivec2, const glm::ivec2& cellSize)
	{
		glm::vec3 res(0.f);

		float scaleX = static_cast<float>(Renderer::ViewportSize.x / cellSize.x);
		res.x = ivec2.x * scaleX;
		//res.x = std::max(res.x, (float)((RenderEngine::Renderer::ViewportSize.x - RenderEngine::Renderer::ViewportOffset.x) / cellSize.x));

		float scaleY = static_cast<float>(Renderer::ViewportSize.y / cellSize.y);
		res.y = ivec2.y * scaleY;
		//res.y = std::max(res.y, (float)((RenderEngine::Renderer::ViewportSize.y - RenderEngine::Renderer::ViewportOffset.y) / cellSize.y));

		return res;
	}

	static std::wstring CharStoWstring(const char* str, int last)
	{
		return std::wstring(str[0], str[last]);
	}

	static std::wstring CharStoWstring(const char* str)
	{
		std::string buf(str);
		return std::wstring(buf.begin(), buf.end());
	}

	static std::wstring StringToWstring(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}
};
