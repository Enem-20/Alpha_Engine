#pragma once

#include "../Game/GObject.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/Texture2D.h"
#include "../Scene/Scene.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>

#include <memory>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> pretrywriter;

class Serializer
{
public:
	static rapidjson::StringBuffer Serialize(std::shared_ptr<GObject> object, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(Scene* scene, pretrywriter* writer = nullptr, std::string name = "");

	static void Init()
	{
		names.resize(4);
		names[0] = "x";
		names[1] = "y";
		names[2] = "z";
		names[3] = "w";
	}

	static rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::Sprite> sprite, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::Texture2D> tex2D, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::ShaderProgram> shaderProgram, pretrywriter* writer = nullptr, std::string name = "");

	static rapidjson::StringBuffer  Serialize(glm::ivec2 _ivec2, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(glm::vec2   _vec2, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(glm::ivec3 _ivec3, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(glm::vec3   _vec3, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(glm::ivec4 _ivec4, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(glm::vec4   _vec4, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(glm::mat3   _mat3, pretrywriter* writer = nullptr, std::string name = "");
	static rapidjson::StringBuffer  Serialize(glm::mat4   _mat4, pretrywriter* writer = nullptr, std::string name = "");
private:
	inline static std::vector<std::string> names;
};