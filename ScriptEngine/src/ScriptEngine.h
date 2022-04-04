#pragma once

#ifdef  SCRIPT_ENGINE_EXPORTS 
/*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define DLLEXPORT __declspec(dllimport)  
#endif

#include <sol/sol.hpp>

namespace Components
{
	class LuaScript;
}

class Timer;


class ClassRegistrator;

class DLLEXPORT ScriptProcessor
{
public:
	//ScriptProcessor();
	static sol::state& getL();
	static void init(char** argv);
	static void FirstFrame();
	static void render();

	static void Awake();
	static void Start();
	static void Update();
	static void FixedUpdate();
	static void LastUpdate();

	static void ScriptUpdates();
	static std::shared_ptr<Timer> GeneralTimer();
private:
	static std::shared_ptr<Timer> GenTimer;
	static sol::state L;
};
