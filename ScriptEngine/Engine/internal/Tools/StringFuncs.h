#pragma once

#include "API/ExportPropety.h"

#include <string>

class DLLEXPORT StringFuncs
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

	static std::string RemoveNumbersEnd(const std::string& str)
	{
		size_t i;
		if (str.size() > 0)
		{
			for (i = str.size() - 1; (str[i] >= 'a') && (str[i] <= 'z') && (i > 0); --i)
			{
			}
			return (i > 0) ? str.substr(0, i + 1) : "";
		}
		return "";
	}
};