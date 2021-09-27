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

	LuaScript::LuaScript(LuaScript&& script) noexcept
		: m_path(std::move(script.m_path))
		, m_Awake(std::move(script.m_Awake))
		, m_Start(std::move(script.m_Start))
		, m_Update(std::move(script.m_Update))
		, m_FixedUpdate(std::move(script.m_FixedUpdate))
		, m_LastUpdate(std::move(script.m_LastUpdate))
	{}
	LuaScript::LuaScript(const LuaScript& script)
		: m_path(script.m_path)
		, m_Awake(script.m_Awake)
		, m_Start(script.m_Start)
		, m_Update(script.m_Update)
		, m_FixedUpdate(script.m_FixedUpdate)
		, m_LastUpdate(script.m_LastUpdate)
	{}

	void LuaScript::SetAwake(const sol::protected_function& Awake)
	{
		m_Awake = Awake;
	}

	void LuaScript::SetStart(const sol::protected_function& Start)
	{
		m_Start = Start;
	}

	void LuaScript::SetUpdate(const sol::protected_function& Update)
	{
		m_Update = Update;
	}

	void LuaScript::SetFixedUpdate(const sol::protected_function& FixedUpdate)
	{
		m_FixedUpdate = FixedUpdate;
	}

	void LuaScript::SetLastUpdate(const sol::protected_function& LastUpdate)
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
		ScriptEngine::ScriptProcessor::L["Awake"] = nullptr;
		ScriptEngine::ScriptProcessor::L["Start"] = nullptr;
		ScriptEngine::ScriptProcessor::L["Update"] = nullptr;
		ScriptEngine::ScriptProcessor::L["FixedUpdate"] = nullptr;
		ScriptEngine::ScriptProcessor::L["LastUpdate"] = nullptr;
	}
}