#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"
#include "Serializer.h"

#include <glm/gtc/matrix_transform.hpp>

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
	Serializer::Init();
	

	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

void ResourceManager::UnloadAllResources()
{
	std::ofstream f(m_path + "/res/scene.json");
	f << Serializer::Serialize(Scene::GetInstance()).GetString();
	f.close();
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

std::string ResourceManager::GetLuaScriptPath(const std::string& relativePath)
{
	 return m_path + "/" + relativePath;
}



bool ResourceManager::loadJSONScene(const std::string& relativePath)
{
	const std::string JSONstring = getFileString(relativePath);

	rapidjson::Document d;
	rapidjson::ParseResult parseScene = d.Parse(JSONstring.c_str());

	if (parseScene.IsError())
	{
		std::cerr << "document isn't parse" << std::endl;
	}

	loadJSONShaders(d.FindMember("shaders")->value.GetString());
	loadJSONTextureAtlasses(d.FindMember("textureAtlasses")->value.GetString());
	loadJSONTextures(d.FindMember("textures")->value.GetString());
	loadJSONSprites(d.FindMember("sprites")->value.GetString());
	loadJSONGameOjects(d.FindMember("GameObjects")->value.GetString());

	return true;
}

bool ResourceManager::loadJSONGameOjects(const std::string& relativePath)
{
	std::string JSONGameObjects = getFileString(relativePath);
	rapidjson::Document d;
	rapidjson::ParseResult JSONgameObjects_parsed = d.Parse(JSONGameObjects.c_str());

	if (JSONgameObjects_parsed.IsError())
	{
		std::cerr << "JSON " << relativePath << " can't parse" << std::endl;
	}

	if (d.IsObject())
	{
		std::cout << "that's object" << std::endl;
	}

	for (const auto& it : d.GetArray())
	{
		const std::string GameObjectName = it.FindMember("name")->value.GetString();

		glm::vec3 buf3;
		int itBuf = 0;
		for (const auto& itPosition : it.FindMember("position")->value.GetArray())
		{
			buf3[itBuf] = itPosition.GetDouble();
			++itBuf;
		}

		glm::ivec2 ibuf2;
		itBuf = 0;
		for (const auto& itCellPosition : it.FindMember("cellposition")->value.GetArray())
		{
			ibuf2[itBuf] = itCellPosition.GetInt();
			++itBuf;
		}
		glm::mat4 buf_mat4;
		size_t it_bufmat4Lines = 0;
		size_t it_bufmat4Columns = 0;
		for (const auto& itLines : it.FindMember("model")->value.GetArray())
		{
			
			for (const auto& itColumns : itLines.GetArray())
			{
				buf_mat4[it_bufmat4Lines][it_bufmat4Columns] = itColumns.GetDouble();
				++it_bufmat4Columns;
			}
			it_bufmat4Columns = 0;
			++it_bufmat4Lines;
		}
		it_bufmat4Lines = 0;
		std::unordered_map<std::string, std::variant<Components::LuaScript>> _components;

		if(it.FindMember("Components")->value.IsArray())
			for (const auto& it2 : it.FindMember("Components")->value.GetArray())
				_components.emplace("", Components::LuaScript("", it2.GetString()));
		 
		std::shared_ptr<GameObject> gameObject = std::make_shared<GameObject>(GameObjectName, getSprite(it.FindMember("sprite")->value.GetString()), buf3, ibuf2, glm::mat4(1.f), _components);
	}

	return true;
}

bool ResourceManager::loadJSONSprites(const std::string& relativePath)
{
	std::string JSONsprites = getFileString(relativePath);
	rapidjson::Document d;
	rapidjson::ParseResult JSONsprites_parsed = d.Parse(JSONsprites.c_str());

	auto it = d.Begin();

	while (it != d.End())
	{
		const std::string spriteName = it->FindMember("spriteName")->value.GetString();
		const std::string textureName = it->FindMember("textureName")->value.GetString();
		const std::string shaderName = it->FindMember("shaderName")->value.GetString();
		const glm::vec2 spriteSize = 
			  glm::vec2(it->FindMember("spriteWidth")->value.GetInt(),
						it->FindMember("spriteHeight")->value.GetInt());
		const std::string subTextureName = it->FindMember("subTextureName")->value.GetString();

		loadSprite(spriteName, textureName, shaderName, spriteSize.x, spriteSize.y, subTextureName);

		++it;
	}

	return true;
}

bool ResourceManager::loadJSONTextureAtlasses(const std::string& relativePath)
{
	std::string JSONTextureAtlasses = getFileString(relativePath);

	rapidjson::Document d;

	rapidjson::ParseResult JSONTextureAtlasses_parsed = d.Parse(JSONTextureAtlasses.c_str());

	if (JSONTextureAtlasses_parsed.IsError())
	{
		std::cerr << "JSON " << relativePath << " can't parse";
	}

	for (const auto& it : d.GetArray())
	{
		const std::string name = it.FindMember("name")->value.GetString();
		const std::string filePath = it.FindMember("filePath")->value.GetString();
		const unsigned int width = it.FindMember("width")->value.GetUint();
		const unsigned int height = it.FindMember("height")->value.GetUint();
		const unsigned int subTextureWidth = it.FindMember("subTextureWidth")->value.GetUint();
		const unsigned int subTextureHeight = it.FindMember("subTextureHeight")->value.GetUint();
		std::vector<std::string> subTextures;

		for (auto itSubTextures = it.FindMember("subTextures")->value.Begin(); 
			itSubTextures != it.FindMember("subTextures")->value.End();
			++itSubTextures)
		{
			subTextures.push_back(itSubTextures->GetString());
		}
		loadTextureAtlas(name, filePath, subTextures, subTextureWidth, subTextureHeight);
	}

	return true;
}

bool ResourceManager::loadJSONTextures(const std::string& relativePath)
{
	std::string JSONtextures = getFileString(relativePath);

	rapidjson::Document d;

	rapidjson::ParseResult JSONtextures_parsed = d.Parse(JSONtextures.c_str());
	auto it = d.Begin();
	while (it != d.End())
	{
		std::string Name = it->GetString();
		++it;
		std::string path = it->GetString();
		++it;
		loadTexture(Name, path);
	}

	return true;
}

bool ResourceManager::loadJSONShaders(const std::string& relativePath)
{
	std::string JSONshaders = getFileString(relativePath);
	rapidjson::Document d;

	rapidjson::ParseResult JSONshaders_parsed = d.Parse(JSONshaders.c_str());

	if (JSONshaders_parsed.IsError())
	{
		std::cerr << "JSON " << relativePath << " can't parse";
	}

	for (const auto& itShaders : d.GetArray())
	{
		std::string shaderName = itShaders.FindMember("name")->value.GetString();
		std::string shader_v = itShaders.FindMember("filePath_v")->value.GetString();
		std::string shader_f = itShaders.FindMember("filePath_f")->value.GetString();
		auto ShaderProgram = loadShaders(std::move(shaderName), std::move(shader_v), std::move(shader_f));

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(1080.f), 0.f, static_cast<float>(1080.f), -100.f, 100.f);

		ShaderProgram->setMatrix4("projectionMat", projectionMatrix);

		ShaderProgram->use();
		ShaderProgram->setInt("tex", 0);
		ShaderProgram->setMatrix4("projectionMat", projectionMatrix);
	}


	return true;
}