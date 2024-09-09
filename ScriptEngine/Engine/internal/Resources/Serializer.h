#pragma once


#ifndef SERIALIZER_H
#define SERIALIZER_H


#include "API/ExportPropety.h"

#include <rapidjson/prettywriter.h>
#include "rapidjson/reader.h"

#include <memory>
#include <vector>
#include <array>
#include <string>

#include <unordered_map>

#include <glm/glm.hpp>

typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> prettywriter;
typedef rapidjson::Reader reader;

class Transform;


class DLLEXPORT Serializer
{
public:
	static void Serialize(const std::string& directory);

	static void Serialize(std::shared_ptr<Transform> transform, prettywriter* writer, std::string_view name = "", const std::string& path = "");

	static const rapidjson::StringBuffer Serialize(glm::ivec2 _ivec2, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
	static const rapidjson::StringBuffer Serialize(glm::vec2   _vec2, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
	static const rapidjson::StringBuffer Serialize(glm::ivec3 _ivec3, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
	static const rapidjson::StringBuffer Serialize(glm::vec3   _vec3, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
	static const rapidjson::StringBuffer Serialize(glm::ivec4 _ivec4, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
	static const rapidjson::StringBuffer Serialize(glm::vec4   _vec4, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
	static const rapidjson::StringBuffer Serialize(glm::mat3   _mat3, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
	static const rapidjson::StringBuffer Serialize(glm::mat4   _mat4, prettywriter* writer = nullptr, std::string_view name = "", const std::string& path = "");
private:
	inline static constexpr std::array<std::string_view, 4> names{"x", "y", "z", "w"};
};

#endif // !SERIALIZER