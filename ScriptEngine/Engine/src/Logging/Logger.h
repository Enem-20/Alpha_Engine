#pragma once

#include <memory>
#include <string>

class IP7_Client;
class IP7_Trace;

class Clerk
{
public:
	static std::string LogErr(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string LogInfo(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string LogDbg(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string LogWarn(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	static std::string LogCrit(uint16_t lineNumber, std::string fileName, std::string funcName, std::wstring formatter);
	
private:
	static IP7_Client* client;	
	static IP7_Trace* trace;
};