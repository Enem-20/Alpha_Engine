#include "ScriptEngine.h"

namespace ScriptEngine
{
	void ScriptProcessor::init()
	{
		L.open_libraries(sol::lib::base);
	}
}