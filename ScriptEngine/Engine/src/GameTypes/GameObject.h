#pragma once

#include "../Components/Components.pch"
#include "../UI/Button.h"


#include <vector>
#include <unordered_map>

namespace RenderEngine
{
	class Sprite;
}

class GameObject
{
	friend class Serializer;
	friend class DeserializerObject;
public:
	static GameObject& toNull(GameObject& gameObject);
	static GameObject SetNull();
	static GameObject Null;
public:
	GameObject(const GameObject& gameObject);
	//GameObject(GameObject&&) = default;
	GameObject(std::string name = "",
		std::shared_ptr<Components::Transform> transform = nullptr,
		std::shared_ptr<RenderEngine::Sprite> sprite = nullptr,
		std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts = std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>>(),
		std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons = std::unordered_map<std::string, std::shared_ptr<UI::Button>>(),
		int render_priority = 0);
	void operator=(const GameObject& gameObject);
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

	std::shared_ptr<GameObject> testShared(GameObject gameObject) { return std::make_shared<GameObject>(gameObject); }

	void AddChild(const GameObject& gameObject);
	GameObject& GetChild(int i) const;

	virtual std::shared_ptr<RenderEngine::Sprite> GetSprite() const;
	
public:
	std::shared_ptr<Components::Transform> transform;

	std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts;
	std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons;

	std::vector<std::shared_ptr<GameObject>> children;

	size_t ID;
	std::string name;
	int render_priority;
	bool onGrid;
protected:
	static size_t counter;
	std::shared_ptr<RenderEngine::Sprite> sprite;
private:
	
	GameObject(size_t ID);
};