#pragma once

//#define GENERATETYPE(ClassName)			\
//	inline static const std::string& type = #ClassName;\

#ifdef DLLEXPORT
#define DLLEXPORT __declspec(dllimport)
#else
#define DLLEXPORT __declspec(dllexport)
#endif