#pragma once

#include "Headers.h"

namespace ScriptEngine
{
	class ClassRegistrator;

	class ScriptProcessor
	{
	public:
		//ScriptProcessor();
		inline static sol::state L;
		static void init();
	private:
		
	};
}