#include "Clerk.h"

#include "P7/Headers/GTypes.h"
#include "P7/Headers/P7_Client.h"
#include "P7/Headers/P7_Trace.h"

#include <iostream>

IP7_Client* Clerk::client = P7_Create_Client(TM("/P7.Sink=Console"));
IP7_Trace* Clerk::trace = P7_Create_Trace(Clerk::client, TM("TraceChannel"));

std::string Clerk::LogErr(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter)
{
	if (trace)
	{
		trace->Trace(0, EP7TRACE_LEVEL_ERROR, NULL, 15, fileName.c_str(), funcName.c_str(), formatter.c_str());
	}
	else
	{
		std::cerr << "trace object not found" << std::endl;
	}

	return "";
}

std::string Clerk::LogInfo(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter)
{
	if (trace)
	{
		trace->Trace(0, EP7TRACE_LEVEL_INFO, NULL, 15, fileName.c_str(), funcName.c_str(), formatter.c_str());
	}
	else
	{
		std::cout << "trace object not found" << std::endl;
	}

	return "";
}

std::string Clerk::LogDbg(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter)
{
	if (trace)
	{
		trace->Trace(0, EP7TRACE_LEVEL_DEBUG, NULL, 15, fileName.c_str(), funcName.c_str(), formatter.c_str());
	}
	else
	{
		std::cout << "trace object not found" << std::endl;
	}

	return "";
}

std::string Clerk::LogWarn(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter)
{
	if (trace)
	{
		trace->Trace(0, EP7TRACE_LEVEL_WARNING, NULL, 15, fileName.c_str(), funcName.c_str(), formatter.c_str());
	}
	else
	{
		std::cout << "trace object not found" << std::endl;
	}

	return "";
}

std::string Clerk::LogCrit(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter)
{
	if (trace)
	{
		trace->Trace(0, EP7TRACE_LEVEL_CRITICAL, NULL, 15, fileName.c_str(), funcName.c_str(), formatter.c_str());
	}
	else
	{
		std::cout << "trace object not found" << std::endl;
	}

	return "";
}