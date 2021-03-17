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


void function_CppfromLua()
{
	std::cout << "C From _Lua!" << std::endl;
}

int main(int argc, char** argv)
{
	ScriptEngine::ScriptProcessor::init();
	std::string path = {argv[0]};
	ResourceManager::SetExecutablePath(argv[0]);

	sol::table Lobject = ScriptEngine::ScriptProcessor::L["Helpers"].get_or_create<sol::table>();

	ScriptEngine::ClassRegistrator::Registration(&Lobject);
	ScriptEngine::ScriptProcessor::L.script_file(ResourceManager::GetLuaScriptPath("res/scripts/GObject_test.lua"));

	std::shared_ptr<int> integer;

	std::cout << typeid(integer).name();


#ifdef OGL
	Engine::EngineMain::Init(argv);
#endif

	return 0;
}