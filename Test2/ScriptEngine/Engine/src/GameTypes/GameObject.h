#pragma once

#include "../Components/Components.pch"
#include "../Renderer/Sprite.h"
#include "../Renderer/ShaderProgram.h"
#include "../UI/Button.h"


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
		std::shared_ptr<Components::Transform> transform = nullptr,
		std::shared_ptr<RenderEngine::Sprite> sprite = nullptr,
		std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts = std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>>(),
		std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons = std::unordered_map<std::string, std::shared_ptr<UI::Button>>(),
		int render_priority = 0);
	GameObject(GameObject&&) = delete;
	virtual ~GameObject();
	void Translate(const glm::vec3& position);
	void Teleport(const glm::vec3& position);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);
	void Update();

	Components::Transform& GetTransform() { return *transform; }
	void SetOnGrid(const bool& onGridNew) { onGrid = onGridNew; }
	virtual void render();

	/*virtual void SetSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");*/

	std::shared_ptr<GameObject> testShared(GameObject gameObject) { return std::make_shared<GameObject>(gameObject); }

	void AddChild(const GameObject& gameObject);
	GameObject& GetChild(int i) const;

	virtual std::shared_ptr<RenderEngine::Sprite> GetSprite() const;
	size_t ID;
public:
	std::shared_ptr<Components::Transform> transform;

	std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts;
	std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons;

	std::vector<std::shared_ptr<GameObject>> children;

	std::string name;
	int render_priority;
	bool onGrid;
protected:
	static size_t counter;
	std::shared_ptr<RenderEngine::Sprite> sprite;
};