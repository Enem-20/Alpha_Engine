#pragma once

#include "../../../src/ScriptEngine.h"

#include <sol/sol.hpp>


namespace Components
{
	class LuaScript
	{
	public:
		LuaScript(sol::function& Awake, sol::function& Start, sol::function& Update, sol::function& FixedUpdate, sol::function& LastUpdate);
		LuaScript(std::string name, std::string path);
		void AddAwake(sol::function& Awake);
		void AddStart(sol::function& Start);
		void AddUpdate(sol::function& Update);
		void AddFixedUpdate(sol::function& FixedUpdate);
		void AddLastUpdate(sol::function& LastUpdate);

		void LoadScript();

		void Awake() { m_Awake(); }
		void Start() { m_Start(); }
		void Update(){m_Update();}
		void FixedUpdate() { m_FixedUpdate(); }
		void LastUpdate() { m_LastUpdate(); }

		std::string m_name;
		std::string m_path;
	private:
		sol::function m_Awake;
		sol::function m_Start;
		sol::function m_Update;
		sol::function m_FixedUpdate;
		sol::function m_LastUpdate;
	};
}