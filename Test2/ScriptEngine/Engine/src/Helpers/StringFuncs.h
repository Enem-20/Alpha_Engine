#pragma once

#include <string>

class StringFuncs
{
public:
	static std::string Match(const std::string& str1, const std::string& str2) 
	{ 
		size_t pos = str1.find(str2); 
		return str1.substr(pos, str2.size()); 
	}

	static bool Find(const std::string& str1, const std::string& str2)
	{
		return str1.find(str2) != (size_t)-1 ? true : false;
	}
};