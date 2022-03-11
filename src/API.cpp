#include "API.h"
#include <string>
#include <codecvt>
#include <windows.h>

namespace API
{
	std::string API::executingDirectory = "";

	void API::LoadEngine()
	{
		std::string EnginePath = executingDirectory + "Engine.dll";

		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		std::wstring wide = converter.from_bytes(EnginePath.c_str());

		hEngine = LoadLibrary(EnginePath.c_str());
	}

	void API::Init(std::string executingFilePath)
	{
		size_t found = executingFilePath.find_last_of("/\\");
		executingDirectory = executingFilePath.substr(0, found);

		LoadEngine();
	}
}