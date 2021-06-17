#include "Serializer.h"

#include <sstream>
#include <rapidjson/document.h>

#include "../Scene/Hierarchy.h"
#include "../Resources/ResourceManager.h"

Serializer::Write::Write(const std::string path, rapidjson::StringBuffer* sb)
{
	this->sb = nullptr;
	if (path != "")
	{
		this->sb = sb;
		try
		{
			file.open((ResourceManager::GetPath() + path));
		}
		catch (std::exception exp)
		{
			std::cerr << exp.what() << std::endl;
		}
	}
}

Serializer::Write::~Write()
{
	if (file.is_open())
	{
		file << sb->GetString();
		file.close();
	}
}

const rapidjson::StringBuffer Serializer::Serialize(std::shared_ptr<GameObject> object, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;
	if (!object) { return sb; }
	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartObject();


	writer->Key("name");
	writer->String(object->name.c_str());

	Serialize(object->transform->position, writer, "position");
	Serialize(object->transform->rotation, writer, "rotation");
	Serialize(object->transform->scale, writer, "scale");

	Serialize(std::make_shared<components>(object->scripts, object->buttons), writer, "Components");

	writer->Key("sprite");
	writer->String(object->sprite->name.c_str());
	


	writer->Key("render_priority");
	writer->Int(object->render_priority);

	writer->EndObject();

	return sb;
}
const std::string Serializer::Serialize(Scene* scene, prettywriter* writer, std::string name, std::string path)
{
	std::string ret = "";
	rapidjson::StringBuffer sb;
	if (!scene) { return ""; }

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}

	Write write(path, &sb);

	ret += "[\n";

	writer->StartArray();
	for (const auto& it : Hierarchy::SceneObjects)
	{
		rapidjson::StringBuffer buf = Serialize(it.second, writer);
		ret += buf.GetString();
		ret += '\n';
		buf.Flush();
	}
	writer->EndArray();

	ret += ']';

	return ret;
}

const rapidjson::StringBuffer Serializer::Serialize(std::shared_ptr<components> _components, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;
	if (!_components) { return sb; }
	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();

	for (auto it : _components->scripts)
	{
		writer->StartObject();

		writer->Key("type");
		writer->String("LuaScript");
		writer->Key("path");
		writer->String(it.second->m_path.c_str());
		writer->Key("name");
		writer->String(it.first.c_str());

		writer->EndObject();
	}
	for (auto it : _components->buttons)
	{
		writer->StartObject();

		writer->Key("type");
		writer->String("Button");
		writer->Key("name");
		writer->String(it.first.c_str());

		writer->EndObject();
	}

	writer->EndArray();
	

	return sb;
}

const rapidjson::StringBuffer  Serializer::Serialize(std::shared_ptr<RenderEngine::Sprite> sprite, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;
	if (!sprite) { return sb; }

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}

	Write write(path, &sb);

	writer->StartObject();
	Serialize(sprite->m_Texture, writer, "m_Texture");
	Serialize(sprite->m_position, writer, "m_position");
	Serialize(sprite->m_size, writer, "m_size");
	writer->Key("RenderMode");
	writer->Int(sprite->GetRenderMode());
	writer->EndObject();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(std::shared_ptr<RenderEngine::Texture2D> tex2D, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;
	if (!tex2D) { return sb; }

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}

	Write write(path, &sb);

	writer->StartObject();

	writer->Key("m_width");
	writer->Uint(tex2D->m_width);
	writer->Key("m_height");
	writer->Uint(tex2D->m_height);
	
	writer->Key("m_subTextures");
	writer->StartArray();
	for (const auto& it : tex2D->m_subTextures)
	{
		writer->Key("subName");
		writer->String(it.first.c_str());
		Serialize(it.second.leftBottomUV, writer, "leftBottomUV");
		Serialize(it.second.rightTopUV,   writer, "rightTopUV");
	}
	writer->EndArray();

	writer->EndObject();

	return sb;
}

const rapidjson::StringBuffer  Serializer::Serialize(glm::ivec2 _ivec2, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}

	Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 2; ++i)
	{
		writer->Double(_ivec2[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::vec2   _vec2, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 2; ++i)
	{
		writer->Double(_vec2[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::ivec3 _ivec3, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 3; ++i)
	{
		writer->Int(_ivec3[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::vec3   _vec3, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 3; ++i)
	{
		writer->Double(_vec3[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::ivec4 _ivec4, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 4; ++i)
	{
		writer->Int(_ivec4[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::vec4   _vec4, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 4; ++i)
	{
		writer->Double(_vec4[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::mat3   _mat3, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();
	for (size_t i = 0; i < 3; ++i)
	{
		Serialize(_mat3[i], writer, "vec4");
	}
	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::mat4   _mat4, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	Write write(path, &sb);

	writer->StartArray();
	for (size_t i = 0; i < 4; ++i)
	{
		Serialize(_mat4[i], writer, "vec4");
	}
	writer->EndArray();

	return sb;
}