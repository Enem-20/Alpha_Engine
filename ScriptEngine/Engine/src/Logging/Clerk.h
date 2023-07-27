#pragma once

#include "../../src/ExportPropety.h"

#include <memory>
#include <string>

class IP7_Client;
class IP7_Trace;

class DLLEXPORT Clerk
{
public:
	static std::string Misstep	(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string Knowledge(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string Unravel	(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string Caveat	(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string Fall		(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
private:
	static IP7_Client* client;	
	static IP7_Trace* trace;
};