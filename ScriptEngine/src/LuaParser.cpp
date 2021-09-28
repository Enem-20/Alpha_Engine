#include "LuaParser.h"
#include "../Engine/src/Resources/ResourceManager.h"
#include "../Engine/src/Components/LuaScript.h"
#include "ScriptEngine.h"
#include "../Engine/src/Scene/Hierarchy.h"

#include <filesystem>
#include <fstream>
#include <typeinfo>

namespace ScriptEngine
{
	void LuaParser::SetEvents()
	{
		/*for (const auto& it : std::filesystem::recursive_directory_iterator(m_path))
		{
			auto _filename = it.path().filename();
			if (std::filesystem::is_regular_file(it.status()) && (it.path().extension() == ".lua"))
			{
				ScriptProcessor::L.script_file(ResourceManager::GetLuaScriptPath(it.path().string()));
				
				m_Awake		  = ScriptProcessor::L["Awake"];
				m_Start		  = ScriptProcessor::L["Start"];
				m_Update	  = ScriptProcessor::L["Update"];
				m_FixedUpdate = ScriptProcessor::L["FixedUpdate"];
				m_LastUpdate  = ScriptProcessor::L["LastUodate"];

				Components::LuaScript(m_Awake, m_Start, m_Update, m_FixedUpdate, m_LastUpdate);
			}
		}*/

		/*for (const auto& it : Hierarchy::SceneObjects)
		{
			for (const auto& ComponentsIt : it.second->Components)
			{
				if (typeid(ComponentsIt.second).name() == "std::shared_ptr<GameObject>")
				{

				}
			}
		}*/
	}

	void LuaParser::SetExexcutablePath(const std::string new_path)
	{
		m_path = new_path;
	}
}