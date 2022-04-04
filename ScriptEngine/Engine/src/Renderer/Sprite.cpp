#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

Sprite::Sprite(std::shared_ptr<Texture2D> Texture,
	std::string initialSubTexture,
	std::shared_ptr<ShaderProgram> shaderProgram,
	const glm::vec2& position,
	const glm::vec3& rotation,
	const glm::vec2& size,
	const int RenderMode)
	: m_Texture(std::move(Texture))
	, m_shaderProgram(std::move(shaderProgram))
	, m_position(position)
	, m_rotation(rotation)
	, m_size(size)
	, m_subTextureName(initialSubTexture)
	, RenderMode(RenderMode)
{
	model = glm::mat4(1.f);

	model = glm::rotate(model, glm::radians(0.f), m_rotation);
	model = glm::translate(model, glm::vec3(m_position, 0.f));
	model = glm::scale(model, glm::vec3(m_size, 0.f));

	GLfloat vertexCoords[] =
	{
		//x  y
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f
	};

	auto subTexture = m_Texture->getSubTexture(std::move(initialSubTexture));

	GLfloat textureCoords[] =
	{
		//u  v
		subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
		subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		subTexture.rightTopUV.x, subTexture.leftBottomUV.y
	};

	GLuint indices[] =
	{
		0,1,2,
		2,3,0
	};


	m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GL_FLOAT), RenderMode);
	VertexBufferLayout vertexCoordsLayout;
	vertexCoordsLayout.addElementLayoutFloat(2, false);
	m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

	m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GL_FLOAT), RenderMode);
	VertexBufferLayout textureCoordsLayout;
	textureCoordsLayout.addElementLayoutFloat(2, false);
	m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

	m_IndexBuffer.init(indices, 6);

	m_vertexArray.unbind();
	m_IndexBuffer.unbind();
}

Sprite::Sprite(const Sprite& sprite)
	: RenderMode(sprite.RenderMode)
{
	model = sprite.model;
	m_Texture = sprite.m_Texture;
	m_shaderProgram = sprite.m_shaderProgram;
	m_position = sprite.m_position;
	m_size = sprite.m_size;
	m_rotation = sprite.m_rotation;

	GLfloat vertexCoords[] =
	{
		//x  y
		0.f, 0.f,
		0.f, 1.f,
		1.f, 1.f,
		1.f, 0.f
	};

	auto subTexture = m_Texture->getSubTexture(std::move(m_subTextureName));

	GLfloat textureCoords[] =
	{
		//u  v
		subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
		subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		subTexture.rightTopUV.x, subTexture.leftBottomUV.y
	};

	GLuint indices[] =
	{
		0,1,2,
		2,3,0
	};


	m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GL_FLOAT), RenderMode);
	VertexBufferLayout vertexCoordsLayout;
	vertexCoordsLayout.addElementLayoutFloat(2, false);
	m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLayout);

	m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GL_FLOAT), RenderMode);
	VertexBufferLayout textureCoordsLayout;
	textureCoordsLayout.addElementLayoutFloat(2, false);
	m_vertexArray.addBuffer(m_textureCoordsBuffer, textureCoordsLayout);

	m_IndexBuffer.init(indices, 6);

	m_vertexArray.unbind();
	m_IndexBuffer.unbind();
}

Sprite::Sprite(Sprite&& sprite) noexcept
	: m_Texture(std::move(sprite.m_Texture))
	, m_shaderProgram(std::move(sprite.m_shaderProgram))
	, m_position(std::move(sprite.m_position))
	, m_size(std::move(sprite.m_size))
	, m_rotation(std::move(sprite.m_rotation))
	, m_vertexArray(std::move(sprite.m_vertexArray))
	, m_vertexCoordsBuffer(std::move(sprite.m_vertexCoordsBuffer))
	, m_textureCoordsBuffer(std::move(sprite.m_textureCoordsBuffer))
	, m_IndexBuffer(std::move(sprite.m_IndexBuffer))
	, RenderMode(std::move(sprite.RenderMode))
{
	//m_Texture = std::make_shared<RenderEngine::Texture2D>(std::move(*sprite.m_Texture));
	//m_shaderProgram = std::make_shared<RenderEngine::ShaderProgram>(std::move(*sprite.m_shaderProgram));
	//m_position = std::move(sprite.m_position);
	//m_size = std::move(sprite.m_size);
	//m_rotation = std::move(sprite.m_rotation);

	//m_vertexArray = std::move(sprite.m_vertexArray);
	//m_vertexCoordsBuffer = std::move(sprite.m_vertexCoordsBuffer);
	//m_textureCoordsBuffer = std::move(sprite.m_textureCoordsBuffer);
	//m_IndexBuffer = std::move(sprite.m_IndexBuffer);
	//RenderMode = sprite.RenderMode;
}

void Sprite::Translate(glm::vec3 position)
{
	model = glm::mat4(1.f);

	m_position[0] += position.x;
	m_position[0] += position.y;

	model = glm::scale(model, glm::vec3(m_size, 0.f));
	model = glm::rotate(model, glm::radians(0.f), m_rotation);
	model = glm::translate(model, glm::vec3(m_position, 0.f));
}

void Sprite::Rotate(glm::vec3 rotation)
{

}

void Sprite::Scale(glm::vec3 scale)
{

}

Sprite::~Sprite()
{

}

void Sprite::render(const glm::mat4& model) const
{
	m_shaderProgram->use();

	m_shaderProgram->setMatrix4("modelMat", /*this->*/model);

	glActiveTexture(GL_TEXTURE0);
	m_Texture->bind();

	Renderer::draw(m_vertexArray, m_IndexBuffer, *m_shaderProgram);
}

void Sprite::InstanceRender(glm::mat4 model) const
{
	m_shaderProgram->setMatrix4("modelMat", model);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Sprite::setPosition(const glm::vec2& position)
{
	m_position = position;
}
void Sprite::setSize(const glm::vec2& size)
{
	m_size = size;
}
void Sprite::setRotation(const glm::vec3& rotation)
{
	m_rotation = rotation;
}

glm::vec2 Sprite::getSize() const
{
	return m_size;
}

glm::vec3 Sprite::getRotation() const
{
	return m_rotation;
}

int Sprite::GetRenderMode() const
{
	switch (RenderMode)
	{
	case GL_STATIC_DRAW:
		return 0;
		break;
	case GL_DYNAMIC_DRAW:
		return 1;
		break;
	case GL_STREAM_DRAW:
		return 2;
		break;
	default:
		return -1;
	}
}
