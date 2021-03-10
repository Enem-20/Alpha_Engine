#define OGL
//#define DX9
//#define MTL
//#define VLN

//#define WNS
//#define LNX
//#define MAC
//#define AND
//#define IOS

//#include "main.h"
#include "../ScriptEngine/Engine/src/EngineMain.h"
#include "../ScriptEngine/src/ClassRegistrator.h"

//#include "../ScriptEngine/Engine/src/Game/GObject.h"

//#include <../src/lua.hpp>
//#include "sol/sol.hpp"

#include <iostream>
//#include <typeinfo>
#include <memory>


void function_CppfromLua()
{
	std::cout << "C From _Lua!" << std::endl;
}

int main(int argc, char** argv)
{
	std::shared_ptr<GObject> object_test = std::make_shared<GObject>();
	ScriptEngine::ScriptProcessor::init();
	ScriptEngine::ClassRegistrator::Registration<std::shared_ptr<GObject>>(object_test, "object_test");
	std::string path = {argv[0]};
	object_test->position = glm::vec3(0, 1, 2);
	ResourceManager::SetExecutablePath(argv[0]);
	ScriptEngine::ScriptProcessor::L.script_file(ResourceManager::loadLuaScripts("res/scripts/function_test.lua"));

	std::shared_ptr<int> integer;

	std::cout << typeid(integer).name();
	/*int same = L["multiply"](1, 5);
	std::cout << "Result: " << same;*/


#ifdef OGL
	Engine::EngineMain::Init(argv);
#endif

	return 0;
}