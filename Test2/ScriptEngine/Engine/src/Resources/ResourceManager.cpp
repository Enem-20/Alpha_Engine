#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include <stack>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "stb_image.h"

ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
ResourceManager::TexturesMap ResourceManager::m_textures;
ResourceManager::SpritesMap ResourceManager::m_sprites;
ResourceManager::AnimatedSpritesMap ResourceManager::m_AnimatedSprites;
ResourceManager::LuaScriptsUMap ResourceManager::m_LuaScripts;
std::string ResourceManager::m_path;

void ResourceManager::SetExecutablePath(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

void ResourceManager::UnloadAllResources()
{
	m_shaderPrograms.clear();
	m_textures.clear();
	m_sprites.clear();
	m_AnimatedSprites.clear();
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
	std::ifstream f;
	f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);

	if (!f.is_open())
	{
		std::cerr << "failed to open file: " << relativeFilePath << std::endl;
		system("pause");
		return std::string();
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	f.close();
	return buffer.str();
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader!" << std::endl;
		system("pause");
		return nullptr;
	}
	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader!" << std::endl;
		system("pause");
		return nullptr;
	}

	std::shared_ptr<RenderEngine::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<RenderEngine::ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}
	std::cerr << "Can't load shader program:\n" << "Vertex: " << vertexPath << "\n" << "Fragment: " << fragmentPath << std::endl;
	system("pause");
	return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
	system("pause");
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if (!pixels)
	{
		std::cerr << "Can't load image: " << texturePath << std::endl;
		system("pause");
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Texture2D> newTexture = m_textures.emplace
	(textureName, std::make_shared<RenderEngine::Texture2D>
		(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);

	return newTexture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
	TexturesMap::const_iterator it = m_textures.find(textureName);
	if (it != m_textures.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the texture " << textureName << std::endl;
	system("pause");
	return nullptr;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprite(const std::string& spriteName,
															  const std::string& textureName,
															  const std::string& shaderName,
															  const unsigned int spriteWidth,
															  const unsigned int spriteHeight,
															  const std::string& subTextureName)
{
	auto Texture = getTexture(textureName);

	if (!Texture)
	{
		std::cerr << "Can't find the texture " << textureName << " for the sprite: " << spriteName << std::endl;
		system("pause");
		return nullptr;
	}

	auto Shader = getShaderProgram(shaderName);

	if (!Shader)
	{
		std::cerr << "Can't find the shader program: " << shaderName << " for the sprite: " << spriteName <<  std::endl;
		system("pause");
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Sprite> newSprite = m_sprites.emplace
	(spriteName, std::make_shared<RenderEngine::Sprite>
		(Texture, subTextureName, Shader, 
		 glm::vec2(0.f, 0.f), glm::vec2(spriteWidth,spriteHeight))).first->second;

	return newSprite;
}
std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprite(const std::string& spriteName)
{
	SpritesMap::const_iterator it = m_sprites.find(spriteName);
	if (it != m_sprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the texture " << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManager::loadAnimatedSprite(const std::string& spriteName,
																	  const std::string& textureName,
																	  const std::string& shaderName,
																	  const unsigned int spriteWidth,
																	  const unsigned int spriteHeight,
																	  const std::string& subTextureName)
{
	auto Texture = getTexture(textureName);

	if (!Texture)
	{
		std::cerr << "Can't find the texture " << textureName << " for the sprite: " << spriteName << std::endl;
		system("pause");
		return nullptr;
	}

	auto Shader = getShaderProgram(shaderName);

	if (!Shader)
	{
		std::cerr << "Can't find the shader program: " << shaderName << " for the sprite: " << spriteName << std::endl;
		system("pause");
		return nullptr;
	}

	std::shared_ptr<RenderEngine::AnimatedSprite> newSprite = m_AnimatedSprites.emplace
	(textureName, std::make_shared<RenderEngine::AnimatedSprite>
		(Texture, subTextureName, Shader,
			glm::vec2(0.f, 0.f), glm::vec2(spriteWidth, spriteHeight))).first->second;

	return newSprite;
}

std::shared_ptr<RenderEngine::AnimatedSprite> ResourceManager::getAnimatedSprite(const std::string& spriteName)
{
	auto it = m_AnimatedSprites.find(spriteName);
	if (it != m_AnimatedSprites.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the animated sprite: " << spriteName << std::endl;
	return nullptr;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(std::string textureName,
	std::string texturePath,
	std::vector<std::string> subTextures, 
	const unsigned int subTextureWidth,
	const unsigned int subTextureHeight)
{
	auto Texture = loadTexture(std::move(textureName), std::move(texturePath));
	
	if (Texture)
	{
		const unsigned int textureWidth = Texture->getWidth();
		const unsigned int textureHeight = Texture->getHeight();
		unsigned int currentTextureOffsetX = 0;
		unsigned int currentTextureOffsetY = textureHeight;
		for (auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - subTextureHeight) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX + subTextureWidth) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);
			Texture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

			currentTextureOffsetX += subTextureWidth;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= subTextureHeight;
			}
		}
	}

	return Texture;
}

std::string ResourceManager::loadLuaScript(const std::string& relativePath)
{
	return m_path + "/" + relativePath;
}

void ResourceManager::loadLuaScripts()
{
	for (const auto& it : std::filesystem::recursive_directory_iterator(m_path))
	{
		auto _filename = it.path().filename();
		if (std::filesystem::is_regular_file(it.status()) && (it.path().extension() == ".lua"))
		{
			std::ifstream f;
			f.open(m_path + "/" + it.path().relative_path().string(), std::ios::in);

			if (!f.is_open())
			{
				std::cerr << "failed to open file: " << it.path().relative_path().string() << std::endl;
				system("pause");
			}

			std::stringstream buffer;
			buffer << f.rdbuf();
			m_LuaScripts.emplace(it.path().filename().string(), buffer.str());
			f.close();
		}
	}
}

//void ResourceManager::loadLuaScripts(const std::string& relativePath)
//{
//
//}