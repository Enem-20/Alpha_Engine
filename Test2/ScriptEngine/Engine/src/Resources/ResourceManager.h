#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <vector>
#include <variant>
#include <functional>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>

namespace RenderEngine
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
}

namespace Components
{
	class LuaScript;
}

namespace UI
{
	class Button;
}

class ResourceManager
{
public:
	struct m_Components
	{
		std::unordered_map<std::string, std::shared_ptr<Components::LuaScript>> scripts;
		std::unordered_map<std::string, std::shared_ptr<UI::Button>> buttons;
	};
	static void SetExecutablePath(const std::string& executablePath);
	static void UnloadAllResources();

	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	static std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);
	
	static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
	static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);

	static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
												const std::string& textureName,
												const std::string& shaderName,
												const unsigned int spriteWidth,
												const unsigned int spriteHeight,
												const int RenderMode,
												const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);

	static std::shared_ptr<RenderEngine::AnimatedSprite> loadAnimatedSprite(const std::string& spriteName,
		const std::string& textureName, 
		const std::string& shaderName,
		const unsigned int spriteWidth,
		const unsigned int spriteHeight,
		const std::string& subTextureName = "default");
	static std::shared_ptr<RenderEngine::AnimatedSprite> getAnimatedSprite(const std::string& spriteName);


	static std::shared_ptr<RenderEngine::Texture2D> loadTextureAtlas(std::string textureName,
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
	static bool loadJSONGameOjects(const std::string& relativePath);
	static bool loadJSONSprites(const std::string& relativePath);
	static bool loadJSONTextureAtlasses(const std::string& relativePath);
	static bool loadJSONText(const std::string& relativePath);
	static bool loadJSONTextures(const std::string& relativePath);
	static bool loadJSONShaders(const std::string& relativePath);
	static m_Components loadJSONComponents(const rapidjson::Value& it);

	static std::string GetPath() { return m_path; }
private:
	static std::string getFileString(const std::string& relativeFilePath);

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
	static ShaderProgramsMap m_shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
	static TexturesMap m_textures;

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;
	static SpritesMap m_sprites;

	typedef std::map<const std::string, std::shared_ptr<RenderEngine::AnimatedSprite>> AnimatedSpritesMap;
	static AnimatedSpritesMap m_AnimatedSprites;

	static std::string m_path;
	static std::string relative_sprites;
	static std::string relative_textures;
	static std::string relative_textureAtlasses;
	static std::string relative_shaders;
	static std::string relative_main;
	static std::shared_ptr<std::pair<const std::string, std::function<void(const std::string)>>> loader;

	/*typedef std::unordered_map<std::string, std::string> LuaScriptsUMap;
	static LuaScriptsUMap m_LuaScripts;*/
};
