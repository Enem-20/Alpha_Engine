#pragma once

#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER
#include "API/ExportPropety.h"

#include "Renderer/src/Window.h"

#include "Renderer/src/BaseRenderer.h"

#include "Renderer/src/BaseSprite.h"
#include "ComponentSystem/Collider2D.h"
#include "ComponentSystem/Component.h"

#include "Renderer/src/Vulkan/VulkanRenderer.h"
#include "Renderer/src/BaseShaderProgram.h"
#include "Renderer/src/OGL/OGLTexture2D.h"
#include "Renderer/src/Vulkan/VulkanTexture2D.h"
#include "Renderer/src/Vulkan/CommandBuffer.h"
#include "Renderer/src/Vulkan/CommandPool.h"
#include "Renderer/src/Vulkan/Instance.h"
#include "Renderer/src/Vulkan/IndexBuffer.h"
#include "Renderer/src/Vulkan/ImageView.h"
#include "Renderer/src/Vulkan/DebugMessenger.h"
#include "Renderer/src/Vulkan/VertexBuffer.h"
#include "Renderer/src/Vulkan/WindowSurface.h"
#include "Renderer/src/Vulkan/DescriptorPool.h"
#include "Renderer/src/Vulkan/LogicalDevice.h"
#include "Renderer/src/Vulkan/PhysicalDevice.h"
#include "Renderer/src/Vulkan/RenderPipeline.h"
#include "Renderer/src/Vulkan/RenderPass.h"
#include "Renderer/src/Vulkan/SwapChain.h"
#include "Renderer/src/Vulkan/UniformBuffer.h"
#include "Renderer/src/Vulkan/SyncObjects.h"
#include "Renderer/src/Vulkan/DescriptorSetLayout.h"
#include "Renderer/src/Vulkan/DescriptionSets.h"
#include "Renderer/src/RendererManager.h"

#include <sol/sol.hpp>

#include <rapidjson/document.h>

#include <memory>
#include <unordered_map>
#include <map>
#include <functional>
#include <vector>
#include <utility>
#include <tuple>

#include <memory>
#include <queue>
#include <string>


class Renderer;
class Mesh;
class Transform;

class DLLEXPORT Resource {
public:
	Resource(std::shared_ptr<void> data);
	Resource(const Resource& resource);
	~Resource();
	template<class T>
	std::shared_ptr<T> getResource();
private:
	std::shared_ptr<void> data;
};

class ClassRegistrator;

class DLLEXPORT ResourceManager
{
	friend ClassRegistrator;
public:
	static void SetExecutablePath(const std::string& executablePath);
	static void UnloadAllResources();

	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static void SetLuaState(std::shared_ptr<sol::state> newL);
	static void loadShaders(std::string_view shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	template<class ShaderProgramType>
	static void loadShaderProgram(std::string_view shaderName, const std::string& vertexPath, const std::string& fragmentPath);

	static std::shared_ptr<BaseTexture2D> loadTexture(std::string_view textureName, const std::string& texturePath);


	static std::shared_ptr<BaseSprite> loadSprite(std::string_view spriteName,
		std::string_view textureName,
		std::string_view shaderName,
		std::string_view meshName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		std::string_view subTextureName = "default");


	static std::shared_ptr<BaseTexture2D> loadTextureAtlas(std::string_view textureName,
		const std::string& texturePath,
		std::vector<std::string> subTextures,
		const unsigned int subTextureWidth,
		const unsigned int subTextureHeight);
	static std::string GetLuaScriptPath(const std::string& relativePath);

	static void onBeforeRenderFrame();
	static void onAfterRenderInitialization();

	static void addOnBeforeRenderFrame(std::string_view name, const std::function<void()>& listener);
	static void addOnAfterRenderInitialization(std::string_view name, const std::function<void()>& listener);
	static void removeOnBeforeRenderInitialization(std::string_view name);
	static void removeOnAfterRenderInitialization(std::string_view name);

	static rapidjson::Document documentParse(const std::string& relativePath);

	static std::shared_ptr<Mesh> loadMesh(std::string_view name, const std::string& relativePath);
	static bool loadJSONScene(const std::string& relativePath);
	static bool loadSave(const std::string& relativePath);
	static void loadSaveReal();
	static void loadExecute();
	static std::vector<std::string> getDirectories(const std::string& relativePath);
	[[nodiscard]] static bool loadJSONGameOjects(const std::string& relativePath);
	static std::shared_ptr<Transform> loadJSONTransform(const std::string& path);
	static bool loadJSONSprites(const std::string& relativePath);
	static bool loadJSONTextureAtlasses(const std::string& relativePath);
	static bool loadJSONTextures(const std::string& relativePath);
	static bool loadJSONShaders(const std::string& relativePath);
	static void loadJSONComponents(const rapidjson::Value& it, std::shared_ptr<GameObject> gameObject);

	static std::string GetPath();

	template<class ResourceType>
	static void addResource(ResourceType* resource);

	template<class ResourceType>
	static void removeResource(std::string_view name);

	template<class ResourceType>
	static void freeResource(std::string_view name);

	template<class ResourceType>
	static std::shared_ptr<ResourceType> getResource(std::string_view name);

	template<class ResourceType>
	static std::unordered_map<std::string, Resource>* getResourcesWithType();

	template<class ResourceType, class... Args>
	static std::shared_ptr<ResourceType> makeResource(Args&&... args);

	template<class BaseResourceType, class DerivedResourceType, class... Args>
	static std::shared_ptr<BaseResourceType> makePolymorphicResource(Args&&... args);
private:
	static std::unordered_map<std::string, std::function<void()>> onBeforeRenderFrameListeners;
	static std::unordered_map<std::string, std::function<void() >> onAfterRenderInitializationListeners;

	static std::shared_ptr<sol::state> L;
	static std::string getFileString(const std::string& relativeFilePath);

	static std::unordered_map<size_t, std::unordered_map<std::string, Resource>>* m_resources;
	static std::unordered_map<size_t, std::unordered_map<std::string, Resource>>* getAllResources();

	static std::string m_path;
	static std::string relative_sprites;
	static std::string relative_textures;
	static std::string relative_textureAtlasses;
	static std::string relative_shaders;
	static std::string relative_main;
	static std::queue<std::function<void(std::string, std::string, std::string)>> shaderLoaders;
	static std::queue<std::tuple<std::string, std::string, std::string>> shaderLoaderParameters;
	static std::queue<std::function<void()>> saveLoaders;
};

template<class T>
std::shared_ptr<T> Resource::getResource() {
	return std::reinterpret_pointer_cast<T>(data);
}


template<class ResourceType>
void ResourceManager::addResource(ResourceType* resource) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");

	auto resourcesByType = getAllResources()->find(ResourceType::type_hash);
	if (resourcesByType != getAllResources()->end()) {
		if (!resourcesByType->second.contains(resource->name)) {
			std::shared_ptr<ResourceType> toShared(resource);
			resourcesByType->second.emplace(resource->name, Resource{ std::reinterpret_pointer_cast<void>(toShared) });
		}
		else {
			std::cout << "Resource with type " << ResourceType::type << " and name " << resource->name << " already exists and can't be overwritten" << '\n';
			delete resource;
		}
	}
	else {
		std::shared_ptr<ResourceType> toShared(resource);
		(*getAllResources())[ResourceType::type_hash].emplace(resource->name, Resource{std::reinterpret_pointer_cast<void>(toShared)});
	}
}

template<class ResourceType>
void ResourceManager::removeResource(std::string_view name) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");

	auto resourcesByType = getAllResources()->find(ResourceType::type_hash);

	if (resourcesByType != getAllResources()->end()) {
		auto resource = resourcesByType->second.find(name.data());

		if (resource != resourcesByType->second.cend()) {
			resourcesByType->second.erase(name.data());
			if (ResourceType::type_hash == BaseTexture2D::type_hash)
				RendererManager::getRenderer().removeTexture(name);
		}
	}

	//std::cerr << "Error: this resource type doesn't exist" << '\n';
}

template<class ResourceType>
void ResourceManager::freeResource(std::string_view name) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");

	auto resourcesByType = getAllResources()->find(ResourceType::type_hash);

	if (resourcesByType != getAllResources()->end()) {
		auto resource = resourcesByType->second.find(name.data());

		if (resource != resourcesByType->second.cend()) {
			resourcesByType.erase(name.data());

			return;
		}
	}

	//std::cerr << "Error: this resource type doesn't exist" << '\n';
}

template<class ResourceType>
std::shared_ptr<ResourceType> ResourceManager::getResource(std::string_view name) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");

	auto resourcesByType = getAllResources()->find(ResourceType::type_hash);
	if (resourcesByType != getAllResources()->cend()) {
		auto resource = resourcesByType->second.find(name.data());

		if (resource != resourcesByType->second.cend()) {
			return resource->second.getResource<ResourceType>();
		}
	}
	//std::cerr << "Error: this resource type doesn't exist" << '\n';
	return nullptr;
}

template<class ResourceType>
std::unordered_map<std::string, Resource>* ResourceManager::getResourcesWithType() {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");

	auto resourcesByType = getAllResources()->find(ResourceType::type_hash);
	if (resourcesByType != getAllResources()->cend()) {
		return &(resourcesByType->second);
	}

	//std::cerr << "Error: this resource type doesn't exist" << '\n';
	return nullptr;
}

template<class ResourceType, class... Args>
std::shared_ptr<ResourceType> ResourceManager::makeResource(Args&&... args) {
	static_assert(std::is_base_of<ResourceBase, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");

	std::tuple<Args...> store(args...);
	auto name = std::get<0>(store);
	if (!getResource<ResourceType>(name)) {
		ResourceType* instance = new ResourceType(args...);
		instance = nullptr;
	}

	return getResource<ResourceType>(name);
}

template<class BaseResourceType, class DerivedResourceType, class... Args>
static std::shared_ptr<BaseResourceType> ResourceManager::makePolymorphicResource(Args&&... args) {
	static_assert(std::is_base_of<BaseResourceType, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");
	static_assert(std::is_base_of<DerivedResourceType, ResourceType>::value, "this resource can't be attached due to the class isn't inherit from ResourceBase");

	std::tuple<Args...> store(args...);
	auto name = std::get<0>(store);
	if (!getResource<BaseResourceType>(name)) {
		BaseResourceType* instance = new DerivedResourceType(args...);
		instance = nullptr;
	}

	return getResource<BaseResourceType>(name);
}

#endif // !RESOURCEMANAGER