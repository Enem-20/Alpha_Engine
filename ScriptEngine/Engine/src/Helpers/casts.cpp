#include "casts.h"

float Casts::castValueToNewRange(const float oldValue, const glm::vec2& oldRange, const glm::vec2& newRange)
{
	return (((oldValue - oldRange.x) * (newRange.y - newRange.x)) / (oldRange.y - oldRange.x)) + newRange.x;
}

float Casts::castFromFramebufferToNDCrange(const float& oldValue) {
	return castValueToNewRange(oldValue, glm::vec2(0.0f, 1.0f), glm::vec2(-1.0f, 1.0f));
}

std::wstring Casts::CharStoWstring(const char* str, int last)
{
	return std::wstring(str[0], str[last]);
}

std::wstring Casts::CharStoWstring(const char* str)
{
	std::string buf(str);
	return std::wstring(buf.begin(), buf.end());
}

std::wstring Casts::StringToWstring(const std::string& str)
{
	return std::wstring(str.begin(), str.end());
}

char* Casts::wharTochar(const wchar_t* str) {
	char* vOut = new char[wcslen(str) + 1];
	wcstombs_s(NULL, vOut, wcslen(str) + 1, str, wcslen(str) + 1);
	return vOut;
}