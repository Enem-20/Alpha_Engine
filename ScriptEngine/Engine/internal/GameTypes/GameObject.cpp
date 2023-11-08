#include "GameObject.h"

#include "ComponentSystem/LuaScript.h"
#include "ComponentSystem/Transform.h"
#include "Renderer/src/Sprite.h"
#include "UI/Button.h"
#include "Tools/StringFuncs.h"
#include "Logging/Clerk.h"

#include <../glm/glm/vec2.hpp>
#include <../glm/glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

size_t GameObject::counter = 0;

GameObject::GameObject(const std::string& name)
	: ResourceBase(name)
{
#ifdef LOG_INFO
	std::string FuncName("GameObject::GameObject(std::string name, std::shared_ptr<Components::Transform> transform, std::shared_ptr<RenderEngine::Sprite> sprite, std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts, std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons, int render_priority)" + name);
	Clerk::Knowledge(28, __FILE__, FuncName, L"Begin of constructor");
#endif

#ifdef LOG_INFO
	Clerk::Knowledge(41, __FILE__, FuncName, L"Choosing name");
#endif
	auto obj = ResourceManager::getResource<GameObject>(name);
	if (obj)
		this->name = name + StringFuncs::RemoveNumbersEnd(obj->name) + std::to_string(ID = ++counter);
	else if (name == "") {
		this->name = std::to_string(ID = ++counter);
	}
	ResourceManager::addResource<GameObject>(this);
}

GameObject::GameObject(const GameObject& gameObject)
	: components(gameObject.components)
	, children(gameObject.children)
	, ResourceBase(gameObject.name)
{
#ifdef LOG_INFO
	Clerk::Knowledge(102, __FILE__, "GameObject copy constructor", L"Begin of constructor");
#endif

	this->name = StringFuncs::RemoveNumbersEnd(gameObject.name) + std::to_string(ID = ++counter);

	ResourceManager::addResource<GameObject>(this);
}

void GameObject::operator=(const GameObject& gameObject)
{
	children = gameObject.children;
	ID = ++counter;
	this->name = StringFuncs::RemoveNumbersEnd(gameObject.name) + std::to_string(ID);

	components = gameObject.components;
}

GameObject::~GameObject()
{
#ifdef LOG_INFO
	Clerk::Knowledge(148, __FILE__, "GameObject::~GameObject at " + name, L"Clear all data...");
#endif
	children.clear();
	auto sprites = getComponentsWithType<Sprite>();
	if(sprites)
	for (auto sprite : *sprites) {
		ResourceManager::removeResource<Sprite>(sprite.second.getComponentFromView<Sprite>()->name);
	}
	auto panels = getComponentsWithType<Panel>();
	if (panels)
	for (auto panel : *panels) {
		ResourceManager::removeResource<Panel>(panel.second.getComponentFromView<Panel>()->name);
	}

	auto colliders = getComponentsWithType<Collider2D>();
	if(colliders)
	for (auto collider : *colliders) {
		ResourceManager::removeResource<Collider2D>(collider.second.getComponentFromView<Collider2D>()->name);
	}
	components.clear();
}

void GameObject::render(CommandBuffer& commandBuffer, RenderPipeline& renderPipeline, uint32_t currentFrame)
{
#ifdef LOG_INFO
	Clerk::Knowledge(159, __FILE__, "GameObject::render() at " + name, L"Rendering sprites...");
#endif

	auto sprites = getComponentsWithType<Sprite>();
	if (sprites)
		for (auto sprite : *sprites) {
			sprite.second.getComponentFromView<Sprite>()->render(commandBuffer, renderPipeline, currentFrame);
		}

#ifdef LOG_INFO
	Clerk::Knowledge(167, __FILE__, "GameObject::render() at " + name, L"Rendering childs...");
#endif
	for (auto it : children)
	{
		it->render(commandBuffer, renderPipeline, currentFrame);
	}
}

void GameObject::Translate(const glm::vec3& position)
{
	auto transform = getComponent<Transform>(name);
	transform->Translate(position);
	SetColliderTransform(transform);

	for (auto it : children)
	{
		it->Translate(position);
	}
}

void GameObject::Teleport(const glm::vec3& position)
{
	auto transform = getComponent<Transform>(name);
	transform->Teleport(position);
	SetColliderTransform(transform);

	for (auto& it : children)
	{
		it->Teleport(position);
	}
}

void GameObject::Rotate(const glm::vec3& rotation)
{
	auto transform = getComponent<Transform>(name);
	transform->Rotate(rotation);
	SetColliderTransform(transform);

	for (auto it : children)
	{
		it->Rotate(rotation);
	}
}

void GameObject::Scale(const glm::vec3& scale)
{
	auto transform = getComponent<Transform>(name);
	transform->Scale(scale);
	SetColliderTransform(transform);

	for (auto it : children)
	{
		it->Scale(scale);
	}
}

void GameObject::Start() {
	auto scripts = getComponentsWithType<LuaScript>();
	if (scripts)
		for (auto sprite : *scripts) {
			sprite.second.getComponentFromView<LuaScript>()->Start();
		}
}

void GameObject::Update(uint32_t currentImage)
{
	auto scripts = getComponentsWithType<LuaScript>();
	if (scripts)
		for (auto sprite : *scripts) {
			sprite.second.getComponentFromView<LuaScript>()->Update(currentImage);
		}

	auto sprites = getComponentsWithType<Sprite>();
	if (sprites)
		for (auto sprite : *sprites) {
			sprite.second.getComponentFromView<Sprite>()->Update(currentImage);
		}
}

void GameObject::AddChild(std::shared_ptr<GameObject> gameObject) {
	gameObject->parent = ResourceManager::getResource<GameObject>(name);
	children.push_back(gameObject);
}
std::shared_ptr<GameObject> GameObject::GetChild(int i) {
	return children[i];
}

GameObject::GameObject(size_t ID)
	: ResourceBase("GameObject")
{
	this->ID = ID;
}

std::string& GameObject::Name(){
	return name;
}

void GameObject::SetColliderTransform(std::shared_ptr<Transform> transform) {
	auto collider = getComponent<Collider2D>(name);
	if(collider)
		collider->SetTransform(transform);
}