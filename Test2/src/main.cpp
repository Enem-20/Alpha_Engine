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
	sol::table Lobject = ScriptEngine::ScriptProcessor::L["Helpers"].get_or_create<sol::table>();
	/*ScriptEngine::ClassRegistrator::Reg_vec2(&Lobject);
	ScriptEngine::ClassRegistrator::Reg_vec3(&Lobject);*/
	ScriptEngine::ClassRegistrator::Registration(&Lobject);
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