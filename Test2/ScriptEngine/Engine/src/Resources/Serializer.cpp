#include "Serializer.h"

rapidjson::StringBuffer Serializer::Serialize(std::shared_ptr<GObject> object, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;
	if (!object) { return sb; }
	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartObject();

	Serialize(object->position, writer, "position");
	Serialize(object->cellposition, writer, "cellposition");
	writer->Key("name");
	writer->String(object->name.c_str());
	Serialize(object->model, writer, "model");
	Serialize(object->sprite, writer, "sprite");

	writer->EndObject();

	return sb;
}
rapidjson::StringBuffer Serializer::Serialize(Scene* scene, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;
	if (!scene) { return sb; }

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();
	for (const auto& it : Hierarchy::SceneObjects)
	{
		Serialize(it.second, writer, it.first);
	}
	writer->EndArray();

	return sb;
}

rapidjson::StringBuffer  Serializer::Serialize(std::shared_ptr<RenderEngine::Sprite> sprite, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;
	if (!sprite) { return sb; }

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartObject();
	Serialize(sprite->m_Texture, writer, "m_Texture");
	Serialize(sprite->m_position, writer, "m_position");
	Serialize(sprite->m_size, writer, "m_size");
	writer->Key("m_rotation");
	writer->Double(sprite->m_rotation);
	writer->EndObject();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(std::shared_ptr<RenderEngine::Texture2D> tex2D, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;
	if (!tex2D) { return sb; }

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartObject();

	writer->Key("m_width");
	writer->Uint(tex2D->m_width);
	writer->Key("m_height");
	writer->Uint(tex2D->m_height);
	
	writer->Key("m_subTextures");
	writer->StartArray();
	for (const auto& it : tex2D->m_subTextures)
	{
		Serialize(it.second.leftBottomUV, writer, "leftBottomUV");
		Serialize(it.second.rightTopUV,   writer, "rightTopUV");
	}
	writer->EndArray();

	writer->EndObject();

	return sb;
}

rapidjson::StringBuffer  Serializer::Serialize(glm::ivec2 _ivec2, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();

	for (size_t i = 0; i < 2; ++i)
	{
		writer->Key(names[i].c_str());
		writer->Double(_ivec2[i]);
	}

	writer->EndArray();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(glm::vec2   _vec2, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();

	for (size_t i = 0; i < 2; ++i)
	{
		writer->Key(names[i].c_str());
		writer->Double(_vec2[i]);
	}

	writer->EndArray();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(glm::ivec3 _ivec3, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();

	for (size_t i = 0; i < 3; ++i)
	{
		writer->Key(names[i].c_str());
		writer->Int(_ivec3[i]);
	}

	writer->EndArray();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(glm::vec3   _vec3, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();

	for (size_t i = 0; i < 3; ++i)
	{
		writer->Key(names[i].c_str());
		writer->Double(_vec3[i]);
	}

	writer->EndArray();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(glm::ivec4 _ivec4, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();

	for (size_t i = 0; i < 4; ++i)
	{
		writer->Key(names[i].c_str());
		writer->Int(_ivec4[i]);
	}

	writer->EndArray();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(glm::vec4   _vec4, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();

	for (size_t i = 0; i < 4; ++i)
	{
		writer->Key(names[i].c_str());
		writer->Double(_vec4[i]);
	}

	writer->EndArray();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(glm::mat3   _mat3, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();
	for (size_t i = 0; i < 3; ++i)
	{
		Serialize(_mat3[i], writer, "vec4");
	}
	writer->EndArray();

	return sb;
}
rapidjson::StringBuffer  Serializer::Serialize(glm::mat4   _mat4, pretrywriter* writer, std::string name)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new pretrywriter(sb);
	}

	writer->StartArray();
	for (size_t i = 0; i < 4; ++i)
	{
		Serialize(_mat4[i], writer, "vec4");
	}
	writer->EndArray();

	return sb;
}