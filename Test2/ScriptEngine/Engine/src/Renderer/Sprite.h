#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

#include <memory>
#include <string>

class Serializer;
class DeserializerSprite;

namespace RenderEngine
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
		friend Serializer;
		friend DeserializerSprite;
	public:
		//Sprite() = default;
		Sprite(std::shared_ptr<Texture2D> Texture,
			   std::string initialSubTexture,
			   std::shared_ptr<ShaderProgram> shaderProgram, 
			   const glm::vec2& position = glm::vec2(135.f, 135.f),
			   const glm::vec2& size = glm::vec2(1.f),
			   const float rotation = 0.f);
		~Sprite();

		Sprite() = delete;
		Sprite(const Sprite& sprite);
		Sprite& operator=(const Sprite&) = delete;
		Sprite(Sprite&& sprite) noexcept;

		virtual void render(glm::mat4 model) const;
		virtual void InstanceRender(glm::mat4 model) const;
		void setPosition(const glm::vec2& position);
		glm::vec2 getSize() const;
		float getRotation() const;
		void setSize(const glm::vec2& size);
		void setRotation(const float rotation);
	protected:
		std::shared_ptr<Texture2D> m_Texture;
		std::shared_ptr<ShaderProgram> m_shaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;

		std::string m_subTextureName;
		VertexArray m_vertexArray;
		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_IndexBuffer;
	};
}