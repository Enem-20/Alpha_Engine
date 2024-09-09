#include "ClassRegistrator.h"

#include <glm/glm.hpp>
#include <sol/sol.hpp>

#include "Physics/Raycast.h"

#include "ComponentSystem/Collider2D.h"
#include "ComponentSystem/LuaScript.h"
#include "ComponentSystem/Transform.h"

#include "Renderer/src/Renderer.h"
#include "Renderer/src/ShaderProgram.h"
#include "Renderer/src/Sprite.h"
#include "Renderer/src/Texture2D.h"
#include "Resources/ResourceManager.h"
#include "GameTypes/GameObject.h"
#include "Resources/Mesh.h"

#include "Tools/casts.h"
#include "Tools/StringFuncs.h"
#include "UI/Button.h"
#include "UI/UIelement.h"
#include "Renderer/src/Window.h"
#include "Renderer/src/WindowManager.h"
#include "Tools/Timer.h"
#include "Input/Input.h"
#include "sol2/include/sol/forward.hpp"

#include <memory>
#include <string_view>

//template<class ResourceType>
//void DLLEXPORT ResourceManager::addResource<GameObject>(ResourceType* resource);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::removeResource<GameObject>(const std::string& name);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::freeResource<GameObject>(const std::string& name);
//template<class ResourceType>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::getResource<GameObject>(const std::string& name);
//template<class ResourceType>
//std::unordered_map<std::string, Resource>* DLLEXPORT ResourceManager::getResourcesWithType<GameObject>();
//template<class ResourceType, class... Args>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::makeResource<GameObject>(Args&&... args);
//
//template<class ResourceType>
//void DLLEXPORT ResourceManager::addResource<Collider2D>(ResourceType* resource);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::removeResource<Collider2D>(const std::string& name);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::freeResource<Collider2D>(const std::string& name);
//template<class ResourceType>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::getResource<Collider2D>(const std::string& name);
//template<class ResourceType>
//std::unordered_map<std::string, Resource>* DLLEXPORT ResourceManager::getResourcesWithType<Collider2D>();
//template<class ResourceType, class... Args>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::makeResource<Collider2D>(Args&&... args);
//
//template<class ResourceType>
//void DLLEXPORT ResourceManager::addResource<Panel>(ResourceType* resource);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::removeResource<Panel>(const std::string& name);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::freeResource<Panel>(const std::string& name);
//template<class ResourceType>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::getResource<Panel>(const std::string& name);
//template<class ResourceType>
//std::unordered_map<std::string, Resource>* DLLEXPORT ResourceManager::getResourcesWithType<Panel>();
//template<class ResourceType, class... Args>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::makeResource<Panel>(Args&&... args);
//
//template<class ResourceType>
//void DLLEXPORT ResourceManager::addResource<Sprite>(ResourceType* resource);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::removeResource<Sprite>(const std::string& name);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::freeResource<Sprite>(const std::string& name);
//template<class ResourceType>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::getResource<Sprite>(const std::string& name);
//template<class ResourceType>
//std::unordered_map<std::string, Resource>* DLLEXPORT ResourceManager::getResourcesWithType<Sprite>();
//template<class ResourceType, class... Args>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::makeResource<Sprite>(Args&&... args);
//
//template<class ResourceType>
//void DLLEXPORT ResourceManager::addResource<Renderer>(ResourceType* resource);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::removeResource<Renderer>(const std::string& name);
//template<class ResourceType>
//void DLLEXPORT ResourceManager::freeResource<Renderer>(const std::string& name);
//template<class ResourceType>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::getResource<Renderer>(const std::string& name);
//template<class ResourceType>
//std::unordered_map<std::string, Resource>* DLLEXPORT ResourceManager::getResourcesWithType<Renderer>();
//template<class ResourceType, class... Args>
//std::shared_ptr<ResourceType> DLLEXPORT ResourceManager::makeResource<Renderer>(Args&&... args);

static GameObject GetData(std::shared_ptr<GameObject> gameObject)
{
	return *gameObject;
}

void ClassRegistrator::Reg_GLMvec2(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<glm::vec2>("vec2"
		, "new", sol::constructors<glm::vec2(), glm::vec2(float, float), glm::vec2(const glm::vec2&)>()

		, sol::meta_function::addition, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator+)
		, sol::meta_function::subtraction, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator-)
		, sol::meta_function::multiplication, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator*)
		, sol::meta_function::division, sol::resolve<glm::vec2(const glm::vec2&, const glm::vec2&)>(glm::operator/)

		//, "x", sol::var(&glm::vec2::x)
		//, "y", sol::var(&glm::vec2::y)
	);
}

void ClassRegistrator::Reg_GLMivec2(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<glm::ivec2>("ivec2"
		, "new", sol::constructors<glm::ivec2(), glm::ivec2(int, int), glm::ivec2(const glm::ivec2&)>()

		, sol::meta_function::addition, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator+)
		, sol::meta_function::subtraction, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator-)
		, sol::meta_function::multiplication, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator*)
		, sol::meta_function::division, sol::resolve<glm::ivec2(const glm::ivec2&, const glm::ivec2&)>(glm::operator/)

		//, "x", sol::var(&glm::ivec2::x)
		//, "y", sol::var(&glm::ivec2::y)
	);
}

void ClassRegistrator::Reg_GLMvec3(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<glm::vec3>("vec3",
		"new", sol::constructors<glm::vec3(), glm::vec3(float, float, float), glm::vec3(const glm::vec2&, float), glm::vec3(float, const glm::vec2&), glm::vec3(const glm::vec3&)>()

		, sol::meta_function::addition, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator+)
		, sol::meta_function::subtraction, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator-)
		, sol::meta_function::multiplication, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator*)
		, sol::meta_function::division, sol::resolve<glm::vec3(const glm::vec3&, const glm::vec3&)>(glm::operator/)

		//, "x", sol::var(&glm::vec3::x)
		//, "y", sol::var(&glm::vec3::y)
		//, "z", sol::var(&glm::vec3::z)
	);
}

void ClassRegistrator::Reg_GLMvec4(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<glm::vec4>("vec4",
		"new", sol::constructors<glm::vec4(), glm::vec4(float, float, float, float)
		, glm::vec4(glm::vec2, float, float), glm::vec4(float, float, glm::vec2), glm::vec4(float, glm::vec2, float)
		, glm::vec4(glm::vec2, glm::vec2)
		, glm::vec4(glm::vec3, float), glm::vec4(float, glm::vec3)
		, glm::vec4(glm::vec4)>()

		, sol::meta_function::addition, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator+)
		, sol::meta_function::subtraction, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator-)
		, sol::meta_function::multiplication, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator*)
		//, sol::meta_function::bitwise_xor, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator^)
		, sol::meta_function::division, sol::resolve<glm::vec4(const glm::vec4&, const glm::vec4&)>(glm::operator/)

		//, "x", sol::var(&glm::vec4::x)
		//, "y", sol::var(&glm::vec4::y)
		//, "z", sol::var(&glm::vec4::z)
		//, "w", sol::var(&glm::vec4::w)
	);
}

void ClassRegistrator::Reg_GLMMat3(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<glm::mat3>("mat3",
		"new", sol::constructors<glm::mat3(), glm::mat3(float), glm::mat3(const glm::mat3&), glm::mat3(glm::vec3&, glm::vec3&, glm::vec3&)>()

		, sol::meta_function::addition, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator+)
		, sol::meta_function::subtraction, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator-)
		, sol::meta_function::multiplication, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator*)
		, sol::meta_function::division, sol::resolve<glm::mat3(const glm::mat3&, const glm::mat3&)>(glm::operator/)
	);
}

void ClassRegistrator::Reg_GLMMat4(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<glm::mat4>("mat4",
		"new", sol::constructors<glm::mat4(), glm::mat4(float), glm::mat4(const glm::mat4&), glm::mat4(glm::vec4&, glm::vec4&, glm::vec4&, glm::vec4&)>()

		, sol::meta_function::addition, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator+)
		, sol::meta_function::subtraction, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator-)
		, sol::meta_function::multiplication, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator*)
		, sol::meta_function::division, sol::resolve<glm::mat4(const glm::mat4&, const glm::mat4&)>(glm::operator/)
	);
}

void ClassRegistrator::Reg_ShaderProgram(sol::table* same)
{
	//Reg_GLMMat4(same);
	same->new_usertype<ShaderProgram>("ShaderProgram"
		, "new", sol::factories(&ResourceManager::loadShaders)
		//, "name", &ShaderProgram::name
	);
}

void ClassRegistrator::Reg_SubTexture2D(sol::table* LTexture2D)
{
	LTexture2D->new_usertype<Texture2D::SubTexture2D>("SubTexture2D",
		"new", sol::constructors<Texture2D::SubTexture2D(), Texture2D::SubTexture2D(const glm::vec2, const glm::vec2)>()
		, "leftBottomUV", &Texture2D::SubTexture2D::getLeftBottomUV
		, "rightTopUV", &Texture2D::SubTexture2D::getRightTopUV
	);
}

void ClassRegistrator::Reg_Texture2D(sol::table* same)
{
	if (same != nullptr)
	{
		/*same->new_usertype<Texture2D>("Texture2D"
			, sol::constructors<Texture2D(const GLuint, const GLuint
				, const unsigned char*, const unsigned int, const GLenum, const GLenum)

			, Texture2D(Texture2D&&)>()

			, "addSubTexture", &Texture2D::addSubTexture
			, "getSubTexture", &Texture2D::getSubTexture
			, "getWidth", &Texture2D::getWidth
			, "getHeight", &Texture2D::getHeight
			, "bind", &Texture2D::bind
			);

		Reg_SubTexture2D(same);*/

		same->new_usertype<Texture2D>(Texture2D::type
			, "new", sol::factories([](std::string_view textureName, const std::string &texturePath){
				return ResourceManager::loadTexture(textureName, texturePath);
			})
			, "getWidth", &Texture2D::getWidth
			, "getHeight", &Texture2D::getHeight
			//, "name", &Texture2D::name
		);
	}
}

void ClassRegistrator::Reg_Sprite(sol::table* object)
{
	object->new_usertype<Sprite>("Sprite"
		, "new", sol::factories(&ResourceManager::loadSprite)
		//, "name", &Sprite::name
	);
}

void ClassRegistrator::Reg_UIelement(sol::table* UIElement)
{
	UIElement->new_usertype<UIelement>("UIelement"
		, sol::no_constructor
		, "AddListener", &UIelement::AddListener);
}

void ClassRegistrator::Reg_Transform(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<Transform>("Transform"
		, "new", sol::factories([](std::string_view name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) {
			auto shared = std::make_shared<Transform>(position, rotation, scale); shared->name = name;
			return shared;
			})
		, "getPosition", &Transform::GetPosition
		, "getRotation", &Transform::GetRotation
		, "getScale", &Transform::GetScale
		//, "name", &Transform::name
		);
}

void ClassRegistrator::Reg_GameObject(sol::table* object)
{
	object->new_usertype<GameObject>("GameObject"
		, "new", sol::factories(&ResourceManager::makeResource<GameObject, const std::string&>)
		, "remove", &ResourceManager::removeResource<GameObject>
		, "Translate", &GameObject::Translate
		, "Teleport", &GameObject::Teleport
		, "Rotate", &GameObject::Rotate
		, "AddChild", &GameObject::AddChild
		, "GetChild", &GameObject::GetChild
		//, "name", &GameObject::name
		, "getLuaScript", &GameObject::getComponent<LuaScript>
		, "getTransform", &GameObject::getComponent<Transform>
		, "getCollider2D", &GameObject::getComponent<Collider2D>
		, "getSprite", &GameObject::getComponent<Sprite>
		, "getPanel", &GameObject::getComponent<Panel>
		, "addLuaScript", &GameObject::addComponent<LuaScript>
		, "addTransform", &GameObject::addComponent<Transform>
		, "addCollider2D", &GameObject::addComponent<Collider2D>
		, "addSprite", &GameObject::addComponent<Sprite>
		, "addPanel", &GameObject::addComponent<Panel>
	);
}

void ClassRegistrator::Reg_Collider2D(sol::table* object) {
	object->new_usertype<Collider2D>("Collider2D"
		, "new", sol::factories(&ResourceManager::makeResource <Collider2D, const std::string&>, 
			[](const std::string& name, std::shared_ptr<Transform> transform){
				return ResourceManager::makeResource<Collider2D>(name, transform);
			})
		, "getTransform", &Collider2D::getTransform
		, "getGameObject", &Collider2D::GetGameObject
		//, "name", &Collider2D::name
	);
}

void ClassRegistrator::Reg_Mesh(sol::table* object) {
	object->new_usertype<Mesh>("Mesh"
		, "new", sol::factories(&ResourceManager::loadMesh)
		//, "name", &Mesh::name
	);
}	

void ClassRegistrator::Reg_LuaScript(sol::table* object) {
	object->new_usertype<LuaScript>("LuaScript"
		, "new", sol::factories([](const std::string& name, const std::string& path, std::shared_ptr<sol::state> L){
			std::make_shared<LuaScript>(name, path, L);
		})
		//, "name", &LuaScript::name
	);
}

void ClassRegistrator::Reg_Timer(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<Timer>("Timer"
		, sol::no_constructor
		, "StartTimer", &Timer::StartTimer
		, "EndTimer", &Timer::EndTimer
		, "GetDelta", &Timer::GetDelta
		, "GetTimeSec", &Timer::GetTimeSec
		, "IsStart", &Timer::IsStart
		, "GetStart", &Timer::GetStart
		, "GetEnd", &Timer::GetEnd);
}

void ClassRegistrator::Reg_Window(sol::table* Lnamespace)
{
	/*Lnamespace->new_usertype<Window>("Window"
		, "GetUI", &Window::GetUI);*/
}
void ClassRegistrator::Reg_WindowManager(sol::table* Lnamespace)
{
	/*Lnamespace->new_usertype<WindowManager>("WindowManager"
		, "GetCurrentWindow", &WindowManager::GetCurrentWindow);*/
}

void ClassRegistrator::Reg_Hierarchy(sol::table* hierarchy)
{
	//hierarchy->new_usertype<Hierarchy>("Hierarchy"
	//	, "getObject", &Hierarchy::getOriginalObject

	//	, "removeObject", &Hierarchy::removeObject
	//	, "getGridObject", &Hierarchy::getGridObject
	//	, "addPoolObject", &Hierarchy::addPoolObject
	//	, "getPoolObject", &Hierarchy::getPoolObject
	//	, "removePoolObject", &Hierarchy::removePoolObject
	//	, "addObject", &Hierarchy::addFromScriptObject
	//	, "addGridObject", &Hierarchy::addGridObject);
}

void ClassRegistrator::Reg_ResourceManager(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<ResourceManager>("ResourceManager"
		, sol::no_constructor
		, "loadScene", &::ResourceManager::loadSave
		, "removeGameObject", &ResourceManager::removeResource<GameObject>
		, "getGameObject", &::ResourceManager::getResource<GameObject>
		, "getTexture", &ResourceManager::getResource<Texture2D>
		, "getSprite", &ResourceManager::getResource<Sprite>
		, "getCollider2D", &ResourceManager::getResource<Collider2D>
		, "getShaderProgram", &ResourceManager::getResource<ShaderProgram>
		, "getMesh", &ResourceManager::getResource<Mesh>
		, "getLuaScript", &ResourceManager::getResource<LuaScript>);
}
void ClassRegistrator::Reg_Input(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<Input>("Input"
		, sol::no_constructor
		, "addOnClickListener", &Input::addMouseCallback
		, "removeOnClickListener", &Input::removeMouseCallback
		, "getNDCMousePosition", &Input::getNDCMousePosition);
}

void ClassRegistrator::Reg_StringFuncs(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<StringFuncs>("StringFuncs"
		, sol::no_constructor
		, "Match", &StringFuncs::Match
		, "Find", &StringFuncs::Find);
}

void ClassRegistrator::Reg_Casts(sol::table* Lnamespace)
{
	Lnamespace->new_usertype<Casts>("Casts"
		, sol::no_constructor
		, "castValueToNewRange", &Casts::castValueToNewRange);
}

void ClassRegistrator::Reg_Raycast(sol::table* Lnamespace) {
	Lnamespace->new_usertype<Raycast>("Raycast"
		, sol::constructors<Raycast()>()
		, "closestBodyHit", &Raycast::closestBodyHit
	);
}

int ClassRegistrator::Registration(sol::table* Lnamespace)
{
	if (!IsReg)
	{
		Reg_GLMvec2(Lnamespace);
		Reg_GLMivec2(Lnamespace);
		Reg_GLMvec3(Lnamespace);
		Reg_GLMvec4(Lnamespace);
		Reg_GLMMat3(Lnamespace);
		Reg_GLMMat4(Lnamespace);

		Reg_Texture2D(Lnamespace);
		Reg_Sprite(Lnamespace);
		Reg_ShaderProgram(Lnamespace);
		Reg_GameObject(Lnamespace);
		Reg_Hierarchy(Lnamespace);
		Reg_Timer(Lnamespace);
		Reg_UIelement(Lnamespace);
		Reg_Window(Lnamespace);
		Reg_WindowManager(Lnamespace);
		Reg_Input(Lnamespace);
		Reg_StringFuncs(Lnamespace);
		Reg_Transform(Lnamespace);
		Reg_Collider2D(Lnamespace);
		Reg_ResourceManager(Lnamespace);
		Reg_Casts(Lnamespace);
		Reg_Raycast(Lnamespace);
		Reg_Mesh(Lnamespace);
		Reg_LuaScript(Lnamespace);

		return 0;
	}

	return -1;
}

