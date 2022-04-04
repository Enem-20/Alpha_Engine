#pragma once

#include "../ExportPropety.h"


#include <vector>
#include <unordered_map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Transform;
class LuaScript;
class Sprite;
class Button;

class DLLEXPORT GameObject
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
		std::shared_ptr<Transform> transform = nullptr,
		std::shared_ptr<Sprite> sprite = nullptr,
		std::unordered_map<std::string, std::shared_ptr<LuaScript>> scripts = std::unordered_map<std::string, std::shared_ptr<LuaScript>>(),
		std::unordered_map<std::string, std::shared_ptr<Button>> buttons = std::unordered_map<std::string, std::shared_ptr<Button>>(),
		int render_priority = 0);
	void operator=(const GameObject& gameObject);
	GameObject(GameObject&&) = delete;
	virtual ~GameObject();


	void Translate(const glm::vec3& position);
	void Teleport(const glm::vec3& position);
	void Rotate(glm::vec3 rotation);
	void Scale(glm::vec3 scale);
	void Update();

	const bool& isGrided() const;
	const std::string& Name() const;
	Transform& GetTransform();
	void SetOnGrid(const bool& onGridNew);
	virtual void render();
	std::unordered_map<std::string, std::shared_ptr<LuaScript>> GetScripts() const;
	const int& GetRenderPriority() const;

	std::shared_ptr<GameObject> testShared(GameObject gameObject);

	void AddChild(const GameObject& gameObject);
	GameObject& GetChild(int i) const;

	virtual std::shared_ptr<Sprite> GetSprite() const;
	
public:
	std::shared_ptr<Transform> transform;

	std::unordered_map<std::string, std::shared_ptr<LuaScript>> scripts;
	std::unordered_map<std::string, std::shared_ptr<Button>> buttons;

	std::vector<std::shared_ptr<GameObject>> children;

	size_t ID;
	std::string name;
	int render_priority;
	bool onGrid;
protected:
	static size_t counter;
	std::shared_ptr<Sprite> sprite;
private:
	
	GameObject(size_t ID);
};