#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h>

typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> prettywriter;
typedef rapidjson::Reader reader;

//template<class T>
//class ISerializer
//{
//public:
//	virtual rapidjson::StringBuffer Serialize(prettywriter* writer = nullptr, std::string name = "") = 0;
//	virtual T Deserialize() = 0;
//};