#pragma once

#include "../ExportPropety.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>

#include "../../internal/Renderer/src/Renderer.h"


class DLLEXPORT Casts
{
public:
	static float castValueToNewRange(const float oldValue, const glm::vec2& oldRange, const glm::vec2& newRange)
	{
		return (((oldValue - oldRange.x) * (newRange.y - newRange.x)) / (oldRange.y - oldRange.x)) + newRange.x;
	}

	static float castFromFramebufferToNDCrange(const float& oldValue) {
		return castValueToNewRange(oldValue, glm::vec2(0.0f, 0.0f), glm::vec2(-1.0f, 1.0f));
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
