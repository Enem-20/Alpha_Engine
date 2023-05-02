#pragma once

#include "../ExportPropety.h"

#include "../../internal/Renderer/src/Renderer.h"
//#include <string>
#include "../../internal/ComponentSystem/src/Component.h"



#include <functional>
#include <sol/sol.hpp>

#include <rapidjson/document.h>

#include <memory>
#include <unordered_map>
#include <map>

class SwapChain;
class PhysicalDevice;
class LogicalDevice;
class CommandPool;

class ShaderProgram;
class Texture2D;
class Sprite;
class AnimatedSprite;


class LuaScript;



class Button;


class DLLEXPORT ResourceManager
{
public:
	struct m_Components
	{
		std::unordered_map<std::string, std::shared_ptr<LuaScript>> scripts;
		std::unordered_map<std::string, std::shared_ptr<Button>> buttons;
	};


	static void SetExecutablePath(const std::string& executablePath);
	static void UnloadAllResources();

	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static void SetLuaState(std::shared_ptr<sol::state> newL);
	static std::shared_ptr<ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<ShaderProgram> getShaderProgram(const std::string& shaderName);
	
#ifdef OGL
	static std::shared_ptr<Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
#elif GLFW_INCLUDE_VULKAN
	static std::shared_ptr<Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
#endif

	static std::shared_ptr<Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<Sprite> loadSprite(const std::string& spriteName,
												const std::string& textureName,
												const std::string& shaderName,
												const unsigned int spriteWidth,
												const unsigned int spriteHeight,
												const int RenderMode,
												const std::string& subTextureName = "default");
	static std::shared_ptr<Sprite> getSprite(const std::string& spriteName);

	static std::shared_ptr<AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName, 
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	static std::shared_ptr<AnimatedSprite> getAnimatedSprite(const std::string& spriteName);


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
private:
	static std::shared_ptr<sol::state> L;
	static std::string getFileString(const std::string& relativeFilePath);

	typedef std::map<const std::string, std::shared_ptr<ShaderProgram>> ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	typedef std::map<std::string, std::shared_ptr<Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<Sprite>> SpritesMap;
	static SpritesMap m_sprites;

	typedef std::map<const std::string, std::shared_ptr<AnimatedSprite>> AnimatedSpritesMap;
	static AnimatedSpritesMap m_AnimatedSprites;

	static std::string m_path;
	static std::string relative_sprites;
	static std::string relative_textures;
	static std::string relative_textureAtlasses;
	static std::string relative_shaders;
	static std::string relative_main;
	static std::shared_ptr<std::pair<const std::string, std::function<void(const std::string)>>> loader;

#ifdef GLFW_INCLUDE_VULKAN
	static Renderer renderer;
#endif
};
