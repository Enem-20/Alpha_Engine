#include "LuaParser.h"


#include <filesystem>


namespace ScriptEngine
{
	void LuaParser::SetExexcutablePath(const std::string& new_path)
	{
		m_path = new_path;
	}
}