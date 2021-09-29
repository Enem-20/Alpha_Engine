#pragma once

#include "../GameTypes/GameObject.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/Texture2D.h"
#include "../Scene/Scene.h"

#include <rapidjson/prettywriter.h>

#include <memory>
#include <vector>
//#include <fstream>
#include <unordered_map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> prettywriter;
typedef rapidjson::Reader reader;

class Serializer
{
public:
	struct components
	{
	public:
		components(std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts, std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons)
			:scripts(scripts)
			,buttons(buttons)
		{}
		std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts;
		std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons;
	};

	static void Serialize(std::unordered_map<std::string, std::shared_ptr<GameObject>>& objects, prettywriter* writer);
	static void Serialize(const std::string& path);
	static const rapidjson::StringBuffer Serialize(std::shared_ptr<components> _components, prettywriter* writer = nullptr, std::string name = "", std::string path = "");

	static void Init()
	{
		names.resize(4);
		names[0] = "x";
		names[1] = "y";
		names[2] = "z";
		names[3] = "w";
	}

	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::Sprite> sprite, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::Texture2D> tex2D, prettywriter* writer = nullptr, std::string name = "", std::string path = "");
	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::ShaderProgram> shaderProgram, prettywriter* writer = nullptr, std::string name = "", std::string path = "");

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