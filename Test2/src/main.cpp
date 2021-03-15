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

//#include <iostream>
#include <memory>


void function_CppfromLua()
{
	std::cout << "C From _Lua!" << std::endl;
}

int main(int argc, char** argv)
{
	std::shared_ptr<GObject> object_test = std::make_shared<GObject>();
	ScriptEngine::ScriptProcessor::init();
	std::string path = {argv[0]};
	object_test->position = glm::vec3(0, 1, 2);
	ResourceManager::SetExecutablePath(argv[0]);
	ResourceManager::loadLuaScripts();
	sol::table Lobject = ScriptEngine::ScriptProcessor::L["Helpers"].get_or_create<sol::table>();

	ScriptEngine::ClassRegistrator::Registration(&Lobject);
	ScriptEngine::ScriptProcessor::L.script_file(ResourceManager::loadLuaScript("res/scripts/GObject_test.lua"));

	std::shared_ptr<int> integer;

	std::cout << typeid(integer).name();


#ifdef OGL
	Engine::EngineMain::Init(argv);
#endif

	return 0;
}