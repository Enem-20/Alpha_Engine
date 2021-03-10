#pragma once

#include <functional>

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
		static void GetEvents();
		static void GetFunctions();
	private:
		static std::function<void()> m_Updates;
		static std::function<void()> m_Awakes;
		static std::function<void()> m_FixedUpdates;
		static std::function<void()> m_Starts;
		static std::function<void()> m_LastUpdates;
	};
}