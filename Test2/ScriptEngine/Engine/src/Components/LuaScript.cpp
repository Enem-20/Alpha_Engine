#include "LuaScript.h"
#include "../Resources/ResourceManager.h"

namespace Components
{
	LuaScript::LuaScript(sol::function& Awake, sol::function& Start, sol::function& Update, sol::function& FixedUpdate, sol::function& LastUpdate)
		: m_Awake(Awake)
		, m_Start(Start)
		, m_Update(Update)
		, m_FixedUpdate(FixedUpdate)
		, m_LastUpdate(LastUpdate)
	{}
	LuaScript::LuaScript(std::string name, std::string path, std::shared_ptr<GameObject> gameObject)
		: Component(name, gameObject)
		, m_path(path)
	{
		LoadScript();
	}

	void LuaScript::AddAwake(sol::function& Awake)
	{
		m_Awake = Awake;
	}

	void LuaScript::AddStart(sol::function& Start)
	{
		m_Start = Start;
	}

	void LuaScript::AddUpdate(sol::function& Update)
	{
		m_Update = Update;
	}

	void LuaScript::AddFixedUpdate(sol::function& FixedUpdate)
	{
		m_FixedUpdate = FixedUpdate;
	}

	void LuaScript::AddLastUpdate(sol::function& LastUpdate)
	{
		m_LastUpdate = m_LastUpdate;
	}

	void LuaScript::LoadScript()
	{
		ScriptEngine::ScriptProcessor::L.script_file(ResourceManager::GetLuaScriptPath(m_path));

		m_Awake = ScriptEngine::ScriptProcessor::L["Awake"];
		m_Start = ScriptEngine::ScriptProcessor::L["Start"];
		m_Update = ScriptEngine::ScriptProcessor::L["Update"];
		m_FixedUpdate = ScriptEngine::ScriptProcessor::L["FixedUpdate"];
		m_LastUpdate = ScriptEngine::ScriptProcessor::L["LastUpdate"];
	}
}