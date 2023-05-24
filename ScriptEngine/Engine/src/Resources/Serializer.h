#pragma once

#include <rapidjson/prettywriter.h>

#include <memory>
#include <vector>
#include <string>
//#include <fstream>
#include <unordered_map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> prettywriter;
typedef rapidjson::Reader reader;

class Button;
class LuaScript;
class GameObject;
class Sprite;
class Texture2D;
class ShaderProgram;
class ComponentView;
class Transform;


class Serializer
{
public:
	static void Serialize(std::unordered_map<std::string, std::shared_ptr<GameObject>>& objects, prettywriter* writer);
	static void Serialize(const std::string& directory);
	static const rapidjson::StringBuffer Serialize(std::unordered_map<std::string, std::unordered_map<std::string, ComponentView>>& _components, prettywriter* writer = nullptr, std::string name = "", std::string directory = "");


	static void Init()
	{
		names.resize(4);
		names[0] = "x";
		names[1] = "y";
		names[2] = "z";
		names[3] = "w";
	}

	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<Sprite> sprite, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<Texture2D> tex2D, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<ShaderProgram> shaderProgram, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<Transform> transform, prettywriter* writer = nullptr, std::string name = "", std::string path = "");

	static const rapidjson::StringBuffer Serialize(glm::ivec2 _ivec2, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer Serialize(glm::vec2   _vec2, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer Serialize(glm::ivec3 _ivec3, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer Serialize(glm::vec3   _vec3, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer Serialize(glm::ivec4 _ivec4, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer Serialize(glm::vec4   _vec4, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer Serialize(glm::mat3   _mat3, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer Serialize(glm::mat4   _mat4, prettywriter* writer = nullptr, std::string name = "", std::string path = "");

	//static Hierarchy* Deserialize(std::string path);
private:
	inline static std::vector<std::string> names;
};