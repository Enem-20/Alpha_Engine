#include "LuaScript.h"

namespace Components
{
	LuaScript::LuaScript(sol::function& Awake, sol::function& Start, sol::function& Update, sol::function& FixedUpdate)
		: m_Awake(Awake)
		, m_Start(Start)
		, m_Update(Update)
		, m_FixedUpdate(FixedUpdate)
	{}

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
}