#pragma once

#include "../Renderer/Sprite.h"
#include "../Renderer/ShaderProgram.h"

class GObject
{
public:
	GObject();
	virtual ~GObject();
	void Translate(const glm::vec3 position);

	void Rotate(const float rotation);

	virtual void render();
	virtual void InstanceRender();

	virtual void SetSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	virtual std::shared_ptr<Renderer::Sprite> GetSprite();

	glm::vec3 position;
protected:
	glm::mat4 model;
	std::shared_ptr<Renderer::Sprite> sprite;
	std::shared_ptr<Renderer::ShaderProgram> m_ShaderProgram;
};

