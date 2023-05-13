#pragma once

#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER
#include "../ExportPropety.h"


#include "../../internal/Renderer/src/Window.h"

#include "../../internal/ComponentSystem/src/Component.h"

#include "../../internal/Renderer/src/ShaderProgram.h"
#include "../../internal/Renderer/src/Texture2D.h"
#include "../../internal/Renderer/src/Sprite.h"
#include "../../internal/Renderer/src/Vulkan/CommandBuffer.h"
#include "../../internal/Renderer/src/Vulkan/CommandPool.h"
#include "../../internal/Renderer/src/Vulkan/Instance.h"
#include "../../internal/Renderer/src/Vulkan/IndexBuffer.h"
#include "../../internal/Renderer/src/Vulkan/ImageView.h"
#include "../../internal/Renderer/src/Vulkan/DebugMessenger.h"
#include "../../internal/Renderer/src/Vulkan/VertexBuffer.h"
#include "../../internal/Renderer/src/Vulkan/WindowSurface.h"
#include "../../internal/Renderer/src/Vulkan/DescriptorPool.h"
#include "../../internal/Renderer/src/Vulkan/LogicalDevice.h"
#include "../../internal/Renderer/src/Vulkan/PhysicalDevice.h"
#include "../../internal/Renderer/src/Vulkan/RenderPipeline.h"
#include "../../internal/Renderer/src/Vulkan/SwapChain.h"
#include "../../internal/Renderer/src/Vulkan/UniformBuffer.h"
#include "../../internal/Renderer/src/Vulkan/SyncObjects.h"
#include "../../internal/Renderer/src/Vulkan/DescriptorSetLayout.h"
#include "../../internal/Renderer/src/Vulkan/DescriptionSets.h"

#include <sol/sol.hpp>

#include <rapidjson/document.h>

#include <memory>
#include <unordered_map>
#include <map>
#include <functional>
#include <string>
#include <vector>
#include <utility>

class Renderer;


class Resource {
public:
	Resource(std::shared_ptr<void> data);
	~Resource() {
		data.reset();
	}
	template<class T>
	std::shared_ptr<T> getResource() {
		return std::reinterpret_pointer_cast<T>(data);
	}

	//template<class T>
	//void free() {
	//	delete reinterpret_cast<T*>(data);
	//	data = nullptr;
	//}
private:
	std::shared_ptr<void> data;
};

class DLLEXPORT ResourceManager
{
public:
	//struct m_Components
	//{
	//	std::unordered_map<std::string, std::shared_ptr<LuaScript>> scripts;
	//	std::unordered_map<std::string, std::shared_ptr<Button>> buttons;
	//};


	static void SetExecutablePath(const std::string& executablePath);
	static void UnloadAllResources();

	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static void SetLuaState(std::shared_ptr<sol::state> newL);
	static std::shared_ptr<ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	//static std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& shaderName);

	static std::shared_ptr<Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);

	//static std::shared_ptr<Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<Sprite> loadSprite(const std::string& spriteName,
		const std::string& textureName,
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const int RenderMode,
		const std::string& subTextureName = "default");
	//static std::shared_ptr<Sprite> getSprite(const std::string& spriteName);

	//static std::shared_ptr<AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
	//	const std::string& textureName,
	//	const std::string& shaderName,
	//	const unsigned int spriteWidth,
	//	const unsigned int spriteHeight,
	//	const std::string& subTextureName = "default");
	//static std::shared_ptr<AnimatedSprite> getAnimatedSprite(const std::string& spriteName);


	static std::shared_ptr<Texture2D> loadTextureAtlas(std::string textureName,
		std::string texturePath,
		std::vector<std::string> subTextures,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHeight);
	static std::string GetLuaScriptPath(const std::string& relativePath);

	static rapidjson::Document documentParse(const std::string& relativePath);

	static bool loadJSONScene(const std::string& relativePath);
	static bool loadSave(const std::string relativePath);
	static void loadSaveReal(const std::string& relativePath);
	static void loadExecute();
	[[nodiscard]] static bool loadJSONGameOjects(const std::string& relativePath);
	static bool loadJSONSprites(const std::string& relativePath);
	static bool loadJSONTextureAtlasses(const std::string& relativePath);
	static bool loadJSONTextures(const std::string& relativePath);
	static bool loadJSONShaders(const std::string& relativePath);
	static std::unordered_map<std::string, ComponentView> loadJSONComponents(const rapidjson::Value& it);

	static std::string GetPath();

	template<class ResourceType>
	static void addResource(ResourceType* resource);

	template<class ResourceType>
	static void removeResource(const std::string& name);

	template<class ResourceType>
	static void freeResource(const std::string& name);

	template<class ResourceType>
	static std::shared_ptr<ResourceType> getResource(const std::string& name);

	template<class ResourceType>
	static std::unordered_map<std::string, Resource>* getResourcesWithType();

	template<class ResourceType, class... Args>
	static std::shared_ptr<ResourceType> makeResource(Args&&... args);
private:
//#ifdef GLFW_INCLUDE_VULKAN
//	static std::unique_ptr<Renderer> renderer;
//#endif

	static std::shared_ptr<sol::state> L;
	static std::string getFileString(const std::string& relativeFilePath);

	//typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;
	//static ShaderProgramsMap m_shaderPrograms;

	//typedef std::map<std::string, std::shared_ptr<Texture2D>> TexturesMap;
	//static TexturesMap m_textures;

	//typedef std::map<const std::string, std::shared_ptr<Sprite>> SpritesMap;
	//static SpritesMap m_sprites;

	//typedef std::map<const std::string, std::shared_ptr<AnimatedSprite>> AnimatedSpritesMap;
	//static AnimatedSpritesMap m_AnimatedSprites;

	static std::unordered_map<std::string, std::unordered_map<std::string, Resource>> m_resources;

	static std::string m_path;
	static std::string relative_sprites;
	static std::string relative_textures;
	static std::string relative_textureAtlasses;
	static std::string relative_shaders;
	static std::string relative_main;
	static std::shared_ptr<std::pair<const std::string, std::function<void(const std::string)>>> loader;
};

template<class ResourceType>
void ResourceManager::addResource(ResourceType* resource) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");
	auto resourcesByType = m_resources.find(ResourceType::type);
	std::shared_ptr<ResourceType> toShared(resource);
	if (resourcesByType != m_resources.end()) {

		resourcesByType->second.emplace(resource->name, Resource{ std::reinterpret_pointer_cast<void>(toShared) });
	}
	else {
		//m_resources.emplace(ResourceType::type, std::unordered_map<std::string, Resource>());
		m_resources[ResourceType::type].emplace(resource->name, Resource{ std::reinterpret_pointer_cast<void>(toShared) });
	}
}

template<class ResourceType>
void ResourceManager::removeResource(const std::string& name) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");
	
	auto resourcesByType = m_resources.find(ResourceType::type);

	if (resourcesByType != m_resources.end()) {
		auto resource = resourcesByType->second.find(name);

		if (resource != resourcesByType->second.cend()) {
			resourcesByType->second.erase(name);

			return;
		}
	}

	std::cerr << "Error: this resource type doesn't exist" << '\n';
}

template<class ResourceType>
void ResourceManager::freeResource(const std::string& name) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");
	auto resourcesByType = m_resources.find(ResourceType::type);

	if (resourcesByType != m_resources.end()) {
		auto resource = resourcesByType->second.find(name);

		if (resource != resourcesByType->second.cend()) {
			resourcesByType.erase(name);

			return;
		}
	}

	std::cerr << "Error: this resource type doesn't exist" << '\n';
}

template<class ResourceType>
std::shared_ptr<ResourceType> ResourceManager::getResource(const std::string& name) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");
	auto resourcesByType = m_resources.find(ResourceType::type);
	if (resourcesByType != m_resources.cend()) {
		auto resource = resourcesByType->second.find(name);

		if (resource != resourcesByType->second.cend()) {
			return resource->second.getResource<ResourceType>();
		}
	}
	std::cerr << "Error: this resource type doesn't exist" << '\n';
	return nullptr;
}

template<class ResourceType>
std::unordered_map<std::string, Resource>* ResourceManager::getResourcesWithType() {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");
	auto resourcesByType = m_resources.find(ResourceType::type);
	if (resourcesByType != m_resources.cend()) {
		return &(resourcesByType->second);
	}

	std::cerr << "Error: this resource type doesn't exist" << '\n';
	return nullptr;
}

template<class ResourceType, class... Args>
std::shared_ptr<ResourceType> ResourceManager::makeResource(Args&&... args) {
	ResourceType* instance = new ResourceType(args...);
	return getResource<ResourceType>(instance->name);
}

#endif // !RESOURCEMANAGER