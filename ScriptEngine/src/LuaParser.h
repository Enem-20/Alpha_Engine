#pragma once

#ifndef SCRIPT_ENGINE_H
#define SCRIPT_ENGINE_H

#include<sol/sol.hpp>

namespace ScriptEngine
{
	class LuaParser
	{
	public:
		LuaParser() = delete;
		LuaParser(const LuaParser&) = delete;
		LuaParser(LuaParser&&) = delete;
		~LuaParser() = delete;
		LuaParser& operator=(LuaParser&&) = delete;
	public:
		static void SetEvents();
		static void SetFunctions();
		static void SetExexcutablePath(const std::string& new_path);
	private:
		static sol::protected_function m_Update;
		static sol::protected_function m_Awake;
		static sol::protected_function m_FixedUpdate;
		static sol::protected_function m_Start;
		static sol::protected_function m_LastUpdate;

		static std::string m_path;
	};
}

#endif