#pragma once

#include <sol/sol.hpp>

namespace Components
{
	class LuaScript
	{
	public:
		LuaScript(sol::function& Awake, sol::function& Start, sol::function& Update, sol::function& FixedUpdate);
		void AddAwake(sol::function& Awake);
		void AddStart(sol::function& Start);
		void AddUpdate(sol::function& Update);
		void AddFixedUpdate(sol::function& FixedUpdate);

		std::string name;
		std::string path;
	private:
		sol::function m_Awake;
		sol::function m_Start;
		sol::function m_Update;
		sol::function m_FixedUpdate;
	};
}