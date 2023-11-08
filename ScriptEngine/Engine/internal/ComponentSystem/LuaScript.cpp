#include "LuaScript.h"

#include "Resources/ResourceManager.h"

LuaScript::LuaScript(sol::protected_function& Awake, sol::protected_function& Start, sol::protected_function& Update, sol::protected_function& FixedUpdate, sol::protected_function& LastUpdate)
	: m_Awake(Awake)
	, m_Start(Start)
	, m_Update(Update)
	, m_FixedUpdate(FixedUpdate)
	, m_LastUpdate(LastUpdate)
	, Script(*this)
{}
LuaScript::LuaScript(std::string name, std::string path, std::shared_ptr<sol::state> L, std::shared_ptr<GameObject> gameObject)
	: Component(name, gameObject)
	, Script(*this)
	, m_path(path)
{
	LoadScript(L);
}

LuaScript::LuaScript(LuaScript&& script) noexcept
	: m_path(std::move(script.m_path))
	, m_Awake(std::move(script.m_Awake))
	, m_Start(std::move(script.m_Start))
	, m_Update(std::move(script.m_Update))
	, m_FixedUpdate(std::move(script.m_FixedUpdate))
	, m_LastUpdate(std::move(script.m_LastUpdate))
	, Component(std::move(script.name), std::move(script.gameObject.lock()))
	, Script(std::move(static_cast<Script>(script)))
{}
LuaScript::LuaScript(const LuaScript& script)
	: m_path(script.m_path)
	, m_Awake(script.m_Awake)
	, m_Start(script.m_Start)
	, m_Update(script.m_Update)
	, m_FixedUpdate(script.m_FixedUpdate)
	, m_LastUpdate(script.m_LastUpdate)
	, Component(script.name, script.gameObject.lock())
	, Script(static_cast<Script>(script))
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

void LuaScript::LoadScript(std::shared_ptr<sol::state> L)
{
	L->script_file(ResourceManager::GetLuaScriptPath(m_path));

	m_Awake = (*L)["Awake"];
	m_Start = (*L)["Start"];
	m_Update = (*L)["Update"];
	m_FixedUpdate = (*L)["FixedUpdate"];
	m_LastUpdate = (*L)["LastUpdate"];
	(*L)["Awake"] = nullptr;
	(*L)["Start"] = nullptr;
	(*L)["Update"] = nullptr;
	(*L)["FixedUpdate"] = nullptr;
	(*L)["LastUpdate"] = nullptr;

	Awake();
}

void LuaScript::Awake() { m_Awake(); }
void LuaScript::Start() { m_Start(); }
void LuaScript::Update(uint32_t currentImage) { m_Update(); }
void LuaScript::FixedUpdate() { m_FixedUpdate(); }
void LuaScript::LastUpdate() { m_LastUpdate(); }