#include "ScriptEngine.h"

namespace ScriptEngine
{
	//ScriptProcessor::ScriptProcessor()
	//{
	//	L.open_libraries(sol::lib::base);
	//	/*L["function_CppfromLua"] = function_CppfromLua;
	//	L.script_file("../res/scripts/function_test.lua");*/
	//}

	void ScriptProcessor::init()
	{
		L.open_libraries(sol::lib::base);
	}
}