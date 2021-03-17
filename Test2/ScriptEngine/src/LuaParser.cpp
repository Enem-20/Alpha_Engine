#include "LuaParser.h"
#include "../Engine/src/Resources/ResourceManager.h"
#include "ScriptEngine.h"

#include <filesystem>
#include <fstream>

namespace ScriptEngine
{
	void LuaParser::SetEvents()
	{
		for (const auto& it : std::filesystem::recursive_directory_iterator(m_path))
		{
			auto _filename = it.path().filename();
			if (std::filesystem::is_regular_file(it.status()) && (it.path().extension() == ".lua"))
			{
				/*ScriptProcessor::L.script_file(ResourceManager::GetLuaScriptPath(it.path().string()));
				ScriptProcessor::L["Update"]*/
			}
		}
	}

	void LuaParser::SetExexcutablePath(const std::string new_path)
	{
		m_path = new_path;
	}
}