#define OGL
//#define DX9
//#define MTL
//#define VLN

//#define WNS
//#define LNX
//#define MAC
//#define AND
//#define IOS


#include "../ScriptEngine/Engine/src/EngineMain.h"
#include "../ScriptEngine/src/ClassRegistrator.h"

#include <memory>
#include <thread>

void function_CppfromLua()
{
	std::cout << "C From _Lua!" << std::endl;
}

int main(int argc, char** argv)
{
	
	ScriptEngine::ScriptProcessor::init();
	sol::table Lobject = ScriptEngine::ScriptProcessor::L["Helpers"].get_or_create<sol::table>();
	std::thread th(ScriptEngine::ClassRegistrator::Registration, &Lobject);

	th.join();
	
#ifdef OGL
	Engine::EngineMain::Init(argv);
#endif
	//ScriptEngine::ScriptProcessor::L.script_file(ResourceManager::GetLuaScriptPath("res/scripts/GameObject_test.lua"));
	return 0;
}