#pragma once

#include "../Renderer/Sprite.h"
#include "../Renderer/ShaderProgram.h"

#include <vector>
#include <iostream>
#include <functional>
namespace ScriptEngine
{
	class ClassRegistrator;
}
class GObject
{
	friend ScriptEngine::ClassRegistrator;
public:
	GObject();
	virtual ~GObject();
	void Translate(const glm::vec3 position);

	void Rotate(const float rotation);

	virtual void render();
	//virtual void update() = 0;

	virtual void SetSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	virtual std::shared_ptr<RenderEngine::Sprite> GetSprite();

	glm::vec3 position;
	glm::ivec2 cellposition;

	virtual glm::vec3& Position() { std::cout << std::endl << "Position" << std::endl; return position; }
	virtual glm::ivec2& CellPosition() { return cellposition; }
protected:
	glm::mat4 model;
	std::shared_ptr<RenderEngine::Sprite> sprite;
	std::shared_ptr<RenderEngine::ShaderProgram> m_ShaderProgram;
};