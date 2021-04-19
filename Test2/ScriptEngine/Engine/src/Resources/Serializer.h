#pragma once

#include "../GameTypes/GameObject.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/Texture2D.h"
#include "../Scene/Scene.h"

#include <rapidjson/rapidjson.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

#include <memory>
#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>

typedef rapidjson::PrettyWriter<rapidjson::StringBuffer> prettywriter;
typedef rapidjson::Reader reader;

class Deserializer 
{
public:
	virtual void SetLevel(size_t level){ this->level = level; }
protected:
	virtual bool Null		()														 = 0;
	virtual bool Bool		(bool b)												 = 0;
	virtual bool Int		(int i)													 = 0;
	virtual bool Uint		(unsigned u)											 = 0;
	virtual bool Int64		(int64_t i)												 = 0;
	virtual bool Uint64		(uint64_t u)											 = 0;
	virtual bool Double		(double d)												 = 0;
	virtual bool String		(const char* str, rapidjson::SizeType length, bool copy) = 0;
	virtual bool StartObject()														 = 0;
	virtual bool Key		(const char* str, rapidjson::SizeType length, bool copy) = 0;
	virtual bool EndObject	(rapidjson::SizeType memberCount)						 = 0;
	virtual bool StartArray ()														 = 0;
	virtual bool EndArray	(rapidjson::SizeType elementCount)						 = 0;
	virtual bool RawNumber	(const char* str, rapidjson::SizeType length, bool copy) = 0;
	
	size_t level = 0;
	std::stack<std::string> Keys;
	size_t iter1 = 0;
	size_t iter2 = 0;
};

class Serializer
{
public:
	static const rapidjson::StringBuffer Serialize(std::shared_ptr<GameObject> object, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(Scene* scene, prettywriter* writer = nullptr, std::string name = "");

	static void Init()
	{
		names.resize(4);
		names[0] = "x";
		names[1] = "y";
		names[2] = "z";
		names[3] = "w";
	}

	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::Sprite> sprite, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::Texture2D> tex2D, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer  Serialize(std::shared_ptr<RenderEngine::ShaderProgram> shaderProgram, prettywriter* writer = nullptr, std::string name = "");

	static const rapidjson::StringBuffer Serialize(glm::ivec2 _ivec2, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(glm::vec2   _vec2, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(glm::ivec3 _ivec3, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(glm::vec3   _vec3, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(glm::ivec4 _ivec4, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(glm::vec4   _vec4, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(glm::mat3   _mat3, prettywriter* writer = nullptr, std::string name = "");
	static const rapidjson::StringBuffer Serialize(glm::mat4   _mat4, prettywriter* writer = nullptr, std::string name = "");

	static Hierarchy* Deserialize(std::string path);
private:
	inline static std::vector<std::string> names;
};


//class DeserializerTexture2D final : public Deserializer
//{
//public:
//	std::shared_ptr<RenderEngine::Texture2D> tex2D;
//
//	DeserializerTexture2D() 
//	{ 
//		level = 0; 
//	}
//	std::pair<std::string, RenderEngine::Texture2D::SubTexture2D>* subTexture;
//
//	bool Null()															override
//	{
//		return true;
//	}
//	bool Bool(bool b)													override
//	{
//		return true;
//	}
//	bool Int(int i)														override
//	{
//		return true;
//	}
//	bool Uint(unsigned u)												override
//	{
//		return true;
//	}
//	bool Int64(int64_t i)												override
//	{
//		return true;
//	}
//	bool Uint64(uint64_t u)												override
//	{
//		return true;
//	}
//	bool Double(double d)												override
//	{
//		if (Keys.top() == "leftBottomUV")
//		{
//			subTexture->second.leftBottomUV[iter1] = d;
//		}
//		if (Keys.top() == "rightTopUV")
//		{
//			subTexture->second.leftBottomUV[iter1] = d;
//		}
//		++iter1;
//
//		if (iter1 == 1) { iter1 = 0; }
//		return true;
//	}
//	bool String(const char* str, rapidjson::SizeType length, bool copy)	override
//	{
//		subTexture = new std::pair<std::string, RenderEngine::Texture2D::SubTexture2D>(str, RenderEngine::Texture2D::SubTexture2D());
//		return true;
//	}
//	bool StartObject()													override
//	{
//		return true;
//	}
//	bool Key(const char* str, rapidjson::SizeType length, bool copy)	override
//	{
//		return true;
//	}
//	bool EndObject(rapidjson::SizeType memberCount)						override
//	{
//		return true;
//	}
//	bool StartArray()													override
//	{
//		return true;
//	}
//	bool EndArray(rapidjson::SizeType elementCount)						override
//	{
//		return true;
//	}
//
//	bool RawNumber(const char* str, rapidjson::SizeType length, bool copy)
//	{
//		return true;
//	}
//
//	void GetSubTextureName(std::string& getName)
//	{
//		std::string Buf = Keys.top();
//		Keys.pop();
//		getName = Keys.top();
//		Keys.push(Buf);
//	}
//};
//
//class DeserializerSprite final : public Deserializer
//{
//public:
//	std::shared_ptr<RenderEngine::Sprite> sprite;
//	std::shared_ptr<DeserializerTexture2D> deserializerTex2D;
//
//	DeserializerSprite() 
//	{ 
//		level = 0;
//		deserializerTex2D = std::make_shared<DeserializerTexture2D>();
//		std::shared_ptr<RenderEngine::Texture2D> tex2D = std::make_shared<RenderEngine::Texture2D>();
//
//		deserializerTex2D->tex2D = tex2D;
//	}
//
//	bool Null()															override
//	{
//		return true;
//	}
//	bool Bool(bool b)													override
//	{
//		return true;
//	}
//	bool Int(int i)														override
//	{
//		return true;
//	}
//	bool Uint(unsigned u)												override
//	{
//		return true;
//	}
//	bool Int64(int64_t i)												override
//	{
//		return true;
//	}
//	bool Uint64(uint64_t u)												override
//	{
//		return true;
//	}
//	bool Double(double d)												override
//	{
//		if ((Keys.top() == "x") || (Keys.top() == "y") || (Keys.top() == "z"))
//			Keys.pop();
//		if (Keys.top() == "m_position")
//		{
//			sprite->m_position[iter1] = d;
//		}
//		else if (Keys.top() == "m_size")
//		{
//			sprite->m_position[iter1] = d;
//		}
//		else if (Keys.top() == "m_rotation")
//		{
//			sprite->m_rotation = d;
//		}
//		++iter1;
//		if (iter1 == 3) { ++iter1; }
//
//		return true;
//	}
//	bool String(const char* str, rapidjson::SizeType length, bool copy)	override
//	{
//		return true;
//	}
//	bool StartObject()													override
//	{
//		return true;
//	}
//	bool Key(const char* str, rapidjson::SizeType length, bool copy)	override
//	{
//		Keys.push(str);
//		return true;
//	}
//	bool EndObject(rapidjson::SizeType memberCount)						override
//	{
//		--level;
//		return false;
//	}
//	bool StartArray()													override
//	{
//		return true;
//	}
//	bool EndArray(rapidjson::SizeType elementCount)						override
//	{
//		if (Keys.top() == "m_Texture")
//		{
//			Keys.pop();
//		}
//		--level;
//		if (iter1 == iter2) { iter1 = 0; iter2 = 0; Keys.pop(); }
//
//		return true;
//	}
//
//	bool RawNumber(const char* str, rapidjson::SizeType length, bool copy)
//	{
//		return true;
//	}
//};
//
//class DeserializerObject final : public Deserializer
//{
//public:
//	std::shared_ptr<GameObject> gameObject;
//	std::shared_ptr<DeserializerSprite> deserializerSprite;
//
//	DeserializerObject() 
//	{ 
//		level = 0; 
//		deserializerSprite = std::make_shared<DeserializerSprite>(); 
//		std::shared_ptr<RenderEngine::Sprite> same = std::make_shared<RenderEngine::Sprite>();
//
//		deserializerSprite->sprite = same;
//	}
//
//
//	bool Null() override{ return true; }
//	bool Bool(bool b) override
//	{
//		return true;
//	}
//	bool Int(int i) override
//	{
//		if (Keys.top() == "ivec2")
//		{
//			gameObject->cellposition[iter1] = i;
//
//			(iter1 == 1) ? iter1 = 0 : ++iter1;
//			return true;
//		}
//
//		return false;
//	}
//	bool Uint(unsigned u) override
//	{
//		if (((Keys.top() == "m_width") || (Keys.top() == "m_height")) && (level == 4))
//		{
//			deserializerSprite->deserializerTex2D->Uint(u);
//		}
//		return true;
//	}
//	bool Int64(int64_t i) override{ return true; }
//	bool Uint64(uint64_t u) override{ return true; }
//	bool Double(double d) override
//	{
//		if ((Keys.top() == "x") || (Keys.top() == "y") || (Keys.top() == "z"))
//			Keys.pop();
//
//		if ((Keys.top() == "vec4") && (level == 3))
//		{
//			gameObject->model[iter1][iter2] = d;
//
//			(iter2 == 3) ? iter2 = 0, ++iter1 : ++iter2;
//		}
//		else if (Keys.top() == "vec3" && level == 2)
//		{
//			gameObject->position[iter1] = d;
//
//			(iter1 == 2) ? iter1 = 0 : ++iter1;
//		}
//		else if (((Keys.top() == "vec2") || (Keys.top() == "m_rotation")) && (level == 3))
//		{
//			deserializerSprite->Double(d);
//		}
//		else if ((Keys.top() == "leftBottomUV") || (Keys.top() == "rightTopUV"))
//		{
//			deserializerSprite->deserializerTex2D->Double(d);
//		}
//
//		return true;
//	}
//	bool String(const char* str, rapidjson::SizeType length, bool copy) override
//	{
//		if (Keys.top() == "name")
//		{
//			gameObject->name = str;
//		}
//		else if (Keys.top() == "subName")
//		{
//			deserializerSprite->deserializerTex2D->String(str, 0, false);
//		}
//		Keys.pop();
//
//		return true;
//	}
//	bool StartObject() override
//	{
//		++level;
//		deserializerSprite->StartObject();
//		deserializerSprite->deserializerTex2D->StartObject();
//
//		return true;
//	}
//	bool Key(const char* str, rapidjson::SizeType length, bool copy) override
//	{
//		Keys.push(str);
//		deserializerSprite->Key(str, 0, false);
//		deserializerSprite->deserializerTex2D->Key(str, 0, false);
//
//		return true;
//	}
//	bool EndObject(rapidjson::SizeType memberCount) override
//	{
//		--level;
//		deserializerSprite->EndObject(0);
//		deserializerSprite->deserializerTex2D->EndObject(0);
//
//		return true;
//	}
//	bool StartArray() override
//	{
//		++level;
//		return true;
//	}
//	bool EndArray(rapidjson::SizeType elementCount) override
//	{
//		--level;
//
//		if (Keys.top() == "sprite") 
//		{
//			deserializerSprite->EndArray(0);
//			Keys.pop();
//		}
//		else if (Keys.top() == "m_Texture")
//		{
//			deserializerSprite->deserializerTex2D->EndArray(0);
//			Keys.pop();
//		}
//
//		if (iter1 == iter2) { iter1 = 0; iter2 = 0; Keys.pop();	}
//
//		return true;
//	}
//
//	bool RawNumber(const char* str, rapidjson::SizeType length, bool copy)
//	{
//		return true;
//	}
//
//	bool CheckforSubTextures()
//	{
//		if (Keys.top() == "vec2")
//		{
//			std::string Buf = Keys.top();
//			Keys.pop();
//			return (Keys.top() == "m_subTextures") ? true : false;
//		}
//		return true;
//	}
//};
//
//class DeserializeScene final : public Deserializer
//{
//public:
//	Hierarchy* hierarchy;
//	std::shared_ptr<DeserializerObject> deserializerObject;
//
//	DeserializeScene() 
//	{ 
//		std::shared_ptr<GameObject> same = std::make_shared<GameObject>("same");
//		deserializerObject = std::make_shared<DeserializerObject>();
//		deserializerObject->gameObject = same;
//
//		hierarchy = Hierarchy::GetInstanceHierarchy();
//	}
//
//	bool Null()															override
//	{
//		return true;
//	}
//	bool Bool(bool b)													override
//	{
//		return true;
//	}
//	bool Int(int i)														override
//	{
//		return true;
//	}
//	bool Uint(unsigned u)												override
//	{
//		return true;
//	}
//	bool Int64(int64_t i)												override
//	{
//		return true;
//	}
//	bool Uint64(uint64_t u)												override
//	{
//		return true;
//	}
//	bool Double(double d)												override
//	{
//		deserializerObject->Double(d);
//
//		return true;
//	}
//	bool String(const char* str, rapidjson::SizeType length, bool copy) override
//	{
//		return true;
//	}
//	bool StartObject()													override
//	{
//		++level;
//
//		deserializerObject->StartObject();
//		return true;
//	}
//	bool Key(const char* str, rapidjson::SizeType length, bool copy)	override
//	{
//		return true;
//	}
//	bool EndObject(rapidjson::SizeType memberCount)						override
//	{
//		--level;
//		if (level == 1)
//		{
//			Hierarchy::addObject(deserializerObject->gameObject);
//		}
//		return true;
//	}
//	bool StartArray()													override
//	{
//		++level;
//		deserializerObject->StartArray();
//		return true;
//	}
//	bool EndArray(rapidjson::SizeType elementCount)						override
//	{
//		--level;
//		return true;
//	}
//
//	bool RawNumber(const char* str, rapidjson::SizeType length, bool copy)
//	{
//		return true;
//	}
//};

