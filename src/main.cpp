#define OGL
//#define DX9
//#define MTL
//#define VLN

#define WNS
//#define LNX
//#define MAC
//#define AND
//#define IOS


#include <thread>

#include "../ScriptEngine/src/ScriptEngine.h"
#include "../ScriptEngine/Engine/src/EngineMain.h"
#include "../ScriptEngine/src/ClassRegistrator.h"

#include "sol/sol.hpp"

#ifdef WNS
#include <Windows.h>
#endif


int main(int argc, char** argv)
{
#ifdef NDEBUG
#ifdef WNS
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#else
#ifdef WNS
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
#endif
	ScriptEngine::ScriptProcessor::init();
	sol::table Lobject = ScriptEngine::ScriptProcessor::L["Engine"].get_or_create<sol::table>();
	std::thread th(ScriptEngine::ClassRegistrator::Registration, &Lobject);

	th.join();
	
#ifdef OGL
	Engine::EngineMain::Init(argv);
	ScriptEngine::ScriptProcessor::L.collect_garbage();
#endif
	
	return 0;
}