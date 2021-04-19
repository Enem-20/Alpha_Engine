#pragma once

#include <glad/glad.h>
#include "glm/vec2.hpp"

#include <string>
#include <iostream>
#include <map>

class Serializer;

namespace RenderEngine
{
	class Texture2D
	{
		friend class Serializer;
		friend class DeserializerTexture2D;
	public:
		struct SubTexture2D
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;

			SubTexture2D(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV)
				: leftBottomUV(_leftBottomUV)
				, rightTopUV(_rightTopUV)
			{}
			SubTexture2D()
				: leftBottomUV(0.f)
				, rightTopUV(1.f)
			{}

		};
		Texture2D() = delete;
		Texture2D(const GLuint width, const GLuint height,
			const unsigned char* data, const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		//Texture2D() = default;
		Texture2D(Texture2D& texture2d);
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2d) noexcept;
		Texture2D(Texture2D&& texture2d) noexcept;
		~Texture2D();

		void addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		const SubTexture2D& getSubTexture(const std::string& name) const;
		unsigned int getWidth() const { return m_width; }
		unsigned int getHeight() const { return m_height; }

		void bind() const;

		/*rapidjson::StringBuffer Serialize(prettywriter* writer = nullptr, std::string name = "")
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

			writer->StartObject();

			writer->Key("path");
			writer->String(path.c_str());
			writer->Key("name");
			writer->String(name.c_str());

			writer->Key("m_width");
			writer->Double(m_width);
			writer->Key("m_height");
			writer->Double(m_height);

			writer->Key("m_subTextures");
			writer->StartArray();
			for (auto& it : m_subTextures)
			{
				it.second.leftBottomUV.Serialize(writer, "leftBottomUV");
				it.second.rightTopUV.Serialize(writer, "rightTopUV");
			}
			writer->EndArray();

			writer->EndObject();
		}*/

		std::string path;
		std::string name;
	private:
		GLuint m_ID;
		GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;

		std::map<std::string, SubTexture2D> m_subTextures;
	};
}