#define OGL
//#define DX9
//#define MTL
//#define VLN

//#define LNX
//#define MAC
//#define AND
//#define IOS



#include <thread>
#include <typeinfo>
#include <iostream>

//#include "../ScriptEngine/src/ScriptEngine.h"
//#include "../ScriptEngine/Engine/src/EngineMain.h"
//#include "../ScriptEngine/src/ClassRegistrator.h"
//#include "API.h"
#include "API/ScriptEngineAPI.h"

#ifdef WIN32
#include <Windows.h>

#endif


int main(int argc, char** argv)
{
#ifdef NDEBUG
#ifdef WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
#else
#ifdef WIN32
	ShowWindow(GetConsoleWindow(), SW_SHOW);
#endif
#endif
	
	ScriptEngine::ScriptProcessor::init(argv);
	//API::API::Init(argv[0]);
	
	std::cout << typeid(void).hash_code() << std::endl;
	return 0;
}