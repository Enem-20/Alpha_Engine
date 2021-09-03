#include "LuaScript.h"
#include "../Resources/ResourceManager.h"

namespace Components
{
	LuaScript::LuaScript(sol::protected_function& Awake, sol::protected_function& Start, sol::protected_function& Update, sol::protected_function& FixedUpdate, sol::protected_function& LastUpdate)
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

	void LuaScript::SetAwake(sol::protected_function& Awake)
	{
		m_Awake = Awake;
	}

	void LuaScript::SetStart(sol::protected_function& Start)
	{
		m_Start = Start;
	}

	void LuaScript::SetUpdate(sol::protected_function& Update)
	{
		m_Update = Update;
	}

	void LuaScript::SetFixedUpdate(sol::protected_function& FixedUpdate)
	{
		m_FixedUpdate = FixedUpdate;
	}

	void LuaScript::SetLastUpdate(sol::protected_function& LastUpdate)
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