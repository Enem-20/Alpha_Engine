#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer
{
	Sprite::Sprite(std::shared_ptr<Texture2D> Texture,
		std::string initialSubTexture,
		std::shared_ptr<ShaderProgram> shaderProgram,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation)
		: m_Texture(std::move(Texture))
		, m_shaderProgram(std::move(shaderProgram))
		, m_position(position)
		, m_size(size)
		, m_rotation(rotation)
		{	
		GLfloat vertexCoords[] =
		{
			//x  y
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f
		};
		
		auto subTexture = m_Texture->getSubTexture(std::move(initialSubTexture));

		GLfloat textureCoords[] =
		{
			//u  v
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,

			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
		};
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_vertexCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), & vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glGenBuffers(1, &m_textureCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	void Sprite::Initialize(std::shared_ptr<Texture2D> Texture,
		std::string initialSubTexture,
		std::shared_ptr<ShaderProgram> shaderProgram,
		const glm::vec2& position,
		const glm::vec2& size,
		const float rotation)
	{
		m_Texture = std::move(Texture);
		m_shaderProgram = shaderProgram;
		m_position = position;
		this->m_size = size;


		GLfloat vertexCoords[] =
		{
			//x  y
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f
		};

		auto subTexture = m_Texture->getSubTexture(std::move(initialSubTexture));

		GLfloat textureCoords[] =
		{
			//u  v
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,

			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y
		};
		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_vertexCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glGenBuffers(1, &m_textureCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}

	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &m_vertexCoordsVBO);
		glDeleteBuffers(1, &m_textureCoordsVBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void Sprite::render(glm::mat4 model) const
	{
		m_shaderProgram->use();

		//model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));
		//model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
		//model = glm::translate(model, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.f));
		m_shaderProgram->setMatrix4("modelMat", model);
		glBindVertexArray(m_VAO);
		

		glActiveTexture(GL_TEXTURE0);
		m_Texture->bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void Sprite::InstanceRender(glm::mat4 model) const
	{
		m_shaderProgram->setMatrix4("modelMat", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void Sprite::setPosition(const glm::vec2& position)
	{
		m_position = position;
	}
	void Sprite::setSize(const glm::vec2& size)
	{
		m_size = size;
	}
	void Sprite::setRotation(const float rotation)
	{
		m_rotation = rotation;
	}

	glm::vec2& Sprite::getSize()
	{
		return m_size;
	}
}