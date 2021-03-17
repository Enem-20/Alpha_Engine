#pragma once

#include "../Renderer/Sprite.h"
#include "../Renderer/ShaderProgram.h"

#include <vector>
#include <iostream>
#include <functional>

class GObject
{
	friend class Serializer;
public:
	GObject(std::string name = "");
	virtual ~GObject();
	void Translate(const glm::vec3 position);

	void Rotate(const float rotation);

	virtual void render();

	virtual void SetSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	virtual std::shared_ptr<RenderEngine::Sprite> GetSprite();

	glm::vec3 position;
	glm::ivec2 cellposition;
	std::string name;
protected:
	glm::mat4 model;
	std::shared_ptr<RenderEngine::Sprite> sprite;
	std::shared_ptr<RenderEngine::ShaderProgram> m_ShaderProgram;
};