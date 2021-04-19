#pragma once

#include "../Renderer/Sprite.h"
#include "../Renderer/ShaderProgram.h"
#include "../Components/LuaScript.h"

#include <vector>
#include <iostream>
#include <functional>
#include <stack>
#include <variant>
#include <unordered_map>

class GameObject
{
	friend class Serializer;
	friend class DeserializerObject;
public:
	GameObject() = delete;
	GameObject(const GameObject& gameObject);
	//GameObject(GameObject&&) = default;
	GameObject(std::string name = "",
		std::shared_ptr<RenderEngine::Sprite> sprite = nullptr,
		glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
		glm::ivec2 cellposition = glm::ivec2(0, 0),
		glm::mat4 model = glm::mat4(1.f),
		std::unordered_map<std::string, std::variant<Components::LuaScript>> Components = std::unordered_map<std::string, std::variant<Components::LuaScript>>());
	GameObject(GameObject&&) = delete;
	virtual ~GameObject();
	void Translate(const glm::vec3 position);

	void Rotate(const float rotation);

	virtual void render();

	virtual void SetSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	virtual void SetSpriteCopy(const std::shared_ptr<RenderEngine::Sprite> sprite);
	virtual void SetModel(glm::mat4&& model);
	void Update();

	GameObject& GetRaw(std::shared_ptr<GameObject> gameObject) { return *gameObject; }
	std::shared_ptr<GameObject> testShared(GameObject gameObject) { return std::make_shared<GameObject>(gameObject); }

	virtual std::shared_ptr<RenderEngine::Sprite> GetSprite();

	std::unordered_map<std::string, std::variant<Components::LuaScript>> m_Components;	//first - component name; second - component

	glm::vec3 position;
	glm::ivec2 cellposition;
	std::string name;
protected:
	glm::mat4 model;
	std::shared_ptr<RenderEngine::Sprite> sprite;
	std::shared_ptr<RenderEngine::ShaderProgram> m_ShaderProgram;
};