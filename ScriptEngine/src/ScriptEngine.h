#pragma once

#include <sol/sol.hpp>

namespace Components
{
	class LuaScript;
}

class Timer;

namespace ScriptEngine
{
	class ClassRegistrator;

	class ScriptProcessor
	{
	public:
		//ScriptProcessor();
		inline static sol::state L;
		static void init();

		static void Awake();
		static void Start();
		static void Update();
		static void FixedUpdate();
		static void LastUpdate();

		inline static std::shared_ptr<Timer> GeneralTimer;
	private:
		
	};
}