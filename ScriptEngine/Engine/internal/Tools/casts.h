#pragma once

#include "API/ExportPropety.h"

#include <string>

#include <glm/glm.hpp>

class DLLEXPORT Casts
{
public:
	static float castValueToNewRange(const float oldValue, const glm::vec2& oldRange, const glm::vec2& newRange);

	static float castFromFramebufferToNDCrange(const float& oldValue);

	static std::wstring CharStoWstring(const char* str, int last);

	static std::wstring CharStoWstring(const char* str);

	static std::wstring StringToWstring(const std::string& str);

	static char* wharTochar(const wchar_t* str);
};
