#include "GameObject.h"

#include "../../internal/ComponentSystem/src/LuaScript.h"
#include "../../internal/ComponentSystem/src/Transform.h"
#include "../../internal/Renderer/src/Sprite.h"
#include "../../internal/UI/src/Button.h"
#include "../Helpers/StringFuncs.h"
#include "../Logging/Clerk.h"
#include "../Input/Input.h"

#include <../glm/glm/vec2.hpp>
#include <../glm/glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

size_t GameObject::counter = 0;

GameObject::GameObject(std::string name)
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
	if(obj)
	 this->name = StringFuncs::RemoveNumbersEnd(obj->name) + std::to_string(ID = ++counter);
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
	components.clear();
	//ResourceManager::removeResource<GameObject>(name);
}

void GameObject::render(CommandBuffer& commandBuffer, RenderPipeline& renderPipeline, uint32_t currentFrame)
{
#ifdef LOG_INFO
	Clerk::Knowledge(159, __FILE__, "GameObject::render() at " + name, L"Rendering sprites...");
#endif

	auto sprites = getComponentsWithType<Sprite>();

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
	//if(onGrid)	
	//	Hierarchy::removeGridObject(Input::GetCell(transform->position));

	getComponent<Transform>(name)->Translate(position);
	
	for (auto it : children)
	{
		it->Translate(position);
	}
	//if(onGrid)
	//	Hierarchy::addGridObject(this->name);
}

void GameObject::Teleport(const glm::vec3& position)
{
	getComponent<Transform>(name)->Teleport(position);

	for (auto& it : children)
	{
		it->Teleport(position);
	}
}

void GameObject::Rotate(glm::vec3 rotation)
{
	getComponent<Transform>(name)->Rotate(rotation);


	for (auto it : children)
	{
		it->Rotate(rotation);
	}
}

void GameObject::Scale(glm::vec3 scale)
{
	getComponent<Transform>(name)->Scale(scale);

	for (auto it : children)
	{
		it->Scale(scale);
	}
}

void GameObject::Update(uint32_t currentImage)
{
	auto componentsByType = components.find(Sprite::type);

	for (auto sprite : componentsByType->second) {
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

GameObject& GameObject::toNull(GameObject& gameObject) {
	gameObject.children.clear();
	gameObject.ID = -1;
	gameObject.name = "Null";
	gameObject.components.clear();

	return gameObject;
}

GameObject::GameObject(size_t ID)
	: ResourceBase("GameObject")
{
	this->ID = ID;
}

//GameObject GameObject::SetNull()
//{
//	Null = GameObject(-1);
//	return Null;
//}

const std::string& GameObject::Name() const {
	return name;
}