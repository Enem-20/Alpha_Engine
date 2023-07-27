#pragma once

class GameObject;

#ifdef  ENGINE_EXPORTS 
/*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)  
#else
/*Enabled as "import" in the Client side for using already created dll file*/
#define DLLEXPORT __declspec(dllimport)  
#endif


class DLLEXPORT EngineMain
{
public:
	static void Init(char** argv);
	static void FirstFrame();
private:
	static void render();
	static void ScriptUpdates();
};
