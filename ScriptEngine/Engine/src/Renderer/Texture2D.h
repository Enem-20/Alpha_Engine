#pragma once
#include "../ExportPropety.h"

#include <unordered_map>
#include <string>

#include "glad/glad.h"
#include "glm/vec2.hpp"

class Serializer;

class DLLEXPORT Texture2D
{
	friend class Serializer;
	friend class DeserializerTexture2D;
public:
	struct SubTexture2D
	{
		glm::vec2 leftBottomUV;
		glm::vec2 rightTopUV;

		SubTexture2D(const SubTexture2D& sub);

		SubTexture2D(SubTexture2D&& sub) noexcept;

		SubTexture2D(const glm::vec2 _leftBottomUV, const glm::vec2 _rightTopUV);
		SubTexture2D();

		const glm::vec2& getLeftBottomUV() const;
		const glm::vec2& getRightTopUV() const;

		const SubTexture2D& operator=(const SubTexture2D& second);
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
	unsigned int getWidth() const;
	unsigned int getHeight() const;

	void bind() const;

	std::string path;
	std::string name;
private:
	GLuint m_ID;
	GLenum m_mode;
	unsigned int m_width;
	unsigned int m_height;

	std::unordered_map<std::string, SubTexture2D> m_subTextures;
};
