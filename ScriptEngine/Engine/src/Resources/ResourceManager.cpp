#include "ResourceManager.h"

#include "Serializer.h"

#include "../Scene/Hierarchy.h"

#include "../GameTypes/GameObject.h"

#include "../../internal/Renderer/src/Renderer.h"
#include "Mesh.h"


//#include "../Renderer/AnimatedSprite.h"
//#include "../../../src/ScriptEngine.h"
#include "../../internal/UI/src/Button.h"
#include "../../internal/ComponentSystem/src/Transform.h"
#include "../../internal/ComponentSystem/src/LuaScript.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

#include <glm/gtc/matrix_transform.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "stb_image.h"


std::unordered_map<std::string, std::unordered_map<std::string, Resource>> ResourceManager::m_resources = {};
//std::unique_ptr<Renderer> ResourceManager::renderer = std::make_unique<Renderer>();
//ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
//ResourceManager::TexturesMap ResourceManager::m_textures;
//ResourceManager::SpritesMap ResourceManager::m_sprites;
//ResourceManager::AnimatedSpritesMap ResourceManager::m_AnimatedSprites;
std::shared_ptr<std::pair<const std::string, std::function<void(const std::string)>>> ResourceManager::loader;
std::string ResourceManager::m_path;
std::shared_ptr<sol::state> ResourceManager::L;

Resource::Resource(std::shared_ptr<void> data) : data(data) {}

void ResourceManager::SetLuaState(std::shared_ptr<sol::state> newL)
{
	ResourceManager::L = newL;
}

void ResourceManager::SetExecutablePath(const std::string& executablePath)
{
	//TODO: Serializer::Init();


	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

void ResourceManager::UnloadAllResources()
{
	//TODO: Serializer::Serialize(m_path + "/res/scene.json");
	//m_shaderPrograms.clear();
	//m_textures.clear();
	//m_sprites.clear();
	//m_AnimatedSprites.clear();
	m_resources.clear();
	Hierarchy::Clear();
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
	std::ifstream f;

	f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		f.open(m_path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);

	}
	catch (std::exception exp)
	{
		std::cerr << exp.what() << std::endl;
	}

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

static std::vector<char> readFile(const std::string& filename) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		throw std::runtime_error("failed to open file!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();

	return buffer;
}

std::shared_ptr<ShaderProgram> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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

#ifdef OGL
	std::shared_ptr<ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<ShaderProgram>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled())
	{
		return newShader;
	}
	std::cerr << "Can't load shader program:\n" << "Vertex: " << vertexPath << "\n" << "Fragment: " << fragmentPath << std::endl;
	system("pause");
	return nullptr;
#elif GLFW_INCLUDE_VULKAN
	return makeResource<ShaderProgram>(shaderName, vertexString, fragmentString);;
#endif
}

//std::shared_ptr<ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
//{
//	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
//	if (it != m_shaderPrograms.end())
//	{
//		return it->second;
//	}
//	std::cerr << "Can't find the shader program: " << shaderName << std::endl;
//	system("pause");
//	return nullptr;
//}

#ifdef OGL
std::shared_ptr<Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);

	stbi_uc* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if (!pixels)
	{
		std::cerr << "Can't load image: " << texturePath << std::endl;
		system("pause");
		return nullptr;
	}

	std::shared_ptr<Texture2D> newTexture = m_textures.emplace
	(textureName, std::make_shared<Texture2D>
		(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);

	return newTexture;
}

#elif GLFW_INCLUDE_VULKAN
std::shared_ptr<Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath) {
	int channels = 0;
	int width = 0;
	int height = 0;

	//stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (!pixels)
	{
		std::cerr << "Can't load image: " << texturePath << std::endl;
		system("pause");
		return nullptr;
	}

	auto texture = makeResource<Texture2D>(textureName, width, height, channels, pixels, *getResource<SwapChain>("TestSwapChain"), *getResource<PhysicalDevice>("TestPhysicalDevice"), *getResource<LogicalDevice>("TestLogicalDevice"), *getResource<CommandPool>("TestCommandPool"));
	//m_textures.emplace(textureName, newTexture);
	
	stbi_image_free(pixels);
	return texture;
}
#endif

//std::shared_ptr<Texture2D> ResourceManager::getTexture(const std::string& textureName)
//{
//	TexturesMap::const_iterator it = m_textures.find(textureName);
//	if (it != m_textures.end())
//	{
//		return it->second;
//	}
//	std::cerr << "Can't find the texture " << textureName << std::endl;
//	system("pause");
//	return nullptr;
//}

std::shared_ptr<Sprite> ResourceManager::loadSprite(const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight,
	const int RenderMode,
	const std::string& subTextureName)
{
	auto Texture = getResource<Texture2D>(textureName);

	if (!Texture)
	{
		std::cerr << "Can't find the texture " << textureName << " for the sprite: " << spriteName << std::endl;
		system("pause");
		return nullptr;
	}

	auto Shader = getResource<ShaderProgram>(shaderName);

	if (!Shader)
	{
		std::cerr << "Can't find the shader program: " << shaderName << " for the sprite: " << spriteName << std::endl;
		system("pause");
		return nullptr;
	}

	/*std::shared_ptr<Sprite> newSprite = m_sprites.emplace
	(spriteName, std::make_shared<Sprite>
		(Texture, subTextureName, Shader,
			glm::vec2(0.f, 0.f), glm::vec3(1.f), glm::vec2(spriteWidth, spriteHeight), RenderMode)).first->second;*/


	return makeResource<Sprite>(spriteName, std::shared_ptr<GameObject>(nullptr), Texture, subTextureName, Shader,
		getResource<Mesh>("SpriteMesh"), glm::vec3(0.f, 0.f, 1.0f), glm::vec3(1.f), glm::vec2(spriteWidth, spriteHeight));
}
//std::shared_ptr<Sprite> ResourceManager::getSprite(const std::string& spriteName)
//{
//	SpritesMap::const_iterator it = m_sprites.find(spriteName);
//	if (it != m_sprites.end())
//	{
//		return it->second;
//	}
//	std::cerr << "Can't find the texture " << spriteName << std::endl;
//	return nullptr;
//}

//std::shared_ptr<AnimatedSprite> ResourceManager::loadAnimatedSprite(const std::string& spriteName,
//	const std::string& textureName,
//	const std::string& shaderName,
//	const unsigned int spriteWidth,
//	const unsigned int spriteHeight,
//	const std::string& subTextureName)
//{
//	auto Texture = getTexture(textureName);
//
//	if (!Texture)
//	{
//		std::cerr << "Can't find the texture " << textureName << " for the sprite: " << spriteName << std::endl;
//		system("pause");
//		return nullptr;
//	}
//
//	auto Shader = getShaderProgram(shaderName);
//
//	if (!Shader)
//	{
//		std::cerr << "Can't find the shader program: " << shaderName << " for the sprite: " << spriteName << std::endl;
//		system("pause");
//		return nullptr;
//	}
//
//	std::shared_ptr<AnimatedSprite> newSprite = m_AnimatedSprites.emplace
//	(textureName, std::make_shared<AnimatedSprite>
//		(Texture, subTextureName, Shader,
//			glm::vec2(0.f, 0.f), glm::vec3(0.f), glm::vec2(spriteWidth, spriteHeight))).first->second;
//
//	return newSprite;
//}

//std::shared_ptr<AnimatedSprite> ResourceManager::getAnimatedSprite(const std::string& spriteName)
//{
//	auto it = m_AnimatedSprites.find(spriteName);
//	if (it != m_AnimatedSprites.end())
//	{
//		return it->second;
//	}
//	std::cerr << "Can't find the animated sprite: " << spriteName << std::endl;
//	return nullptr;
//}

std::shared_ptr<Texture2D> ResourceManager::loadTextureAtlas(std::string textureName,
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

rapidjson::Document ResourceManager::documentParse(const std::string& relativePath)
{
	const std::string JSONstring = getFileString(relativePath);

	rapidjson::Document d;
	rapidjson::ParseResult parseScene = d.Parse(JSONstring.c_str());

	if (parseScene.IsError())
	{
		std::cerr << "document isn't parse" << std::endl;
	}

	return d;
}

std::shared_ptr<Mesh> ResourceManager::loadMesh(const std::string& name, const std::string& relativePath) {
	std::unordered_map<Vertex, uint32_t> uniqueVertices{};
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, (m_path + '/' + relativePath).c_str())) {
		throw std::runtime_error(warn + err);
	}

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex{};
			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.color = { 1.0f, 1.0f, 1.0f };
			//vertices.push_back(vertex);

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}
			indices.push_back(uniqueVertices[vertex]);
		}
	}
	//vertices.clear();
	//vertices.push_back(Vertex{ {-1.0f, -1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f} });
	//vertices.push_back(Vertex{ {1.0f, -1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f} });
	//vertices.push_back(Vertex{ {1.0f, 1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f} });
	//vertices.push_back(Vertex{ {-1.0f, 1.0f, 0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f} });

	return makeResource<Mesh>(name, std::move(vertices), std::move(indices));
}

bool ResourceManager::loadJSONScene(const std::string& relativePath)
{
	//GameObject::SetNull();
	UnloadAllResources();
	rapidjson::Document d = documentParse(std::move(relativePath));

	loadJSONShaders(d.FindMember("shaders")->value.GetString());
	loadJSONTextureAtlasses(d.FindMember("textureAtlasses")->value.GetString());
	loadJSONTextures(d.FindMember("textures")->value.GetString());
	loadJSONSprites(d.FindMember("sprites")->value.GetString());
	loadJSONGameOjects(d.FindMember("GameObjects")->value.GetString());
	//loadJSONText("");

	return true;
}

bool ResourceManager::loadSave(const std::string relativePath)
{
	loader = std::make_shared<std::pair<const std::string, std::function<void(const std::string)>>>(relativePath, loadSaveReal);
	return true;
}

void ResourceManager::loadSaveReal(const std::string& relativePath)
{
	UnloadAllResources();

	rapidjson::Document d = documentParse("res/default/main.json");

	loadJSONShaders(d.FindMember("shaders")->value.GetString());
	loadJSONTextureAtlasses(d.FindMember("textureAtlasses")->value.GetString());
	loadJSONTextures(d.FindMember("textures")->value.GetString());
	loadJSONSprites(d.FindMember("sprites")->value.GetString());
	loadJSONGameOjects(/*m_path + '/' +*/relativePath);

	loader = nullptr;
}

void ResourceManager::loadExecute()
{
	if (loader)
		loader->second(loader->first);
}

[[nodiscard]]
bool ResourceManager::loadJSONGameOjects(const std::string& relativePath)
{
	rapidjson::Document d = documentParse(relativePath);

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
			buf3[itBuf] = static_cast<float>(itPosition.GetDouble());
			++itBuf;
		}

		glm::vec3 bufRotation;
		int itVecRotation = 0;
		for (const auto& itRotation : it.FindMember("rotation")->value.GetArray())
		{
			bufRotation[itVecRotation] = static_cast<float>(itRotation.GetDouble());
			++itVecRotation;
		}

		glm::vec3 bufScale;
		int itVecScale = 0;
		for (const auto& itScale : it.FindMember("scale")->value.GetArray())
		{
			bufScale[itVecScale] = static_cast<float>(itScale.GetDouble());
			++itVecScale;
		}

		int render_priority = 0;
		if (it.FindMember("render_priority")->value.IsInt())
			render_priority = it.FindMember("render_priority")->value.GetInt();

		std::string spriteName;
		if (it.FindMember("sprite")->value.IsString())
		{
			spriteName = it.FindMember("sprite")->value.GetString();
		}

		auto gameObject = std::make_shared<GameObject>(GameObjectName);
		loadJSONComponents(it, gameObject);

		gameObject->addComponent<Transform>(std::make_shared<Transform>(buf3, bufRotation, bufScale));
		gameObject->addComponent<Sprite>(getResource<Sprite>(spriteName));
	}

	return true;
}

void ResourceManager::loadJSONComponents(const rapidjson::Value& it, std::shared_ptr<GameObject> gameObject)
{
	//m_Components components;
	std::unordered_map<std::string, ComponentView> components;
	if (it.FindMember("Components")->value.IsArray())
	{
		for (const auto& itComponents : it.FindMember("Components")->value.GetArray())
		{
			std::string type = itComponents.FindMember("type")->value.GetString();
			if (type == "LuaScript")
			{
				gameObject->addComponent<LuaScript>(std::make_shared<LuaScript>(itComponents.FindMember("name")->value.GetString(), itComponents.FindMember("path")->value.GetString(), L));
				//components.scripts.emplace(itComponents.FindMember("name")->value.GetString(), std::make_shared<LuaScript>(itComponents.FindMember("name")->value.GetString(), itComponents.FindMember("path")->value.GetString(), L));
			}
			else if (type == "Button")
			{
				gameObject->addComponent<Button>(std::make_shared<Button>(itComponents.FindMember("name")->value.GetString()));
				//components.buttons.emplace(itComponents.FindMember("name")->value.GetString(), std::make_shared<Button>(itComponents.FindMember("name")->value.GetString()));
			}
		}
	}
}

bool ResourceManager::loadJSONSprites(const std::string& relativePath)
{
	rapidjson::Document d = documentParse(std::move(relativePath));

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

#ifdef OGL
		int RenderMode = it->FindMember("RenderMode")->value.GetInt();

		switch (RenderMode)
		{
		case 0:
			RenderMode = GL_STATIC_DRAW;
			break;
		case 1:
			RenderMode = GL_DYNAMIC_DRAW;
			break;
		case 2:
			RenderMode = GL_STREAM_DRAW;
			break;
		default:
			std::cerr << "Error while load sprite resource " + spriteName;
			RenderMode = 0;
		}
#else
		int RenderMode = 0;
#endif



		loadSprite(spriteName, textureName, shaderName, static_cast<uint32_t>(spriteSize.x), static_cast<uint32_t>(spriteSize.y), RenderMode, subTextureName);

		++it;
	}

	return true;
}

bool ResourceManager::loadJSONTextureAtlasses(const std::string& relativePath)
{
	rapidjson::Document d = documentParse(std::move(relativePath));

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
	rapidjson::Document d = documentParse(std::move(relativePath));
	auto it = d.Begin();
	while (it != d.End())
	{
		std::string Name = it->GetString();
		++it;
		std::string path = it->GetString();
		++it;
		loadTexture(Name, path);//remake
	}

	return true;
}

bool ResourceManager::loadJSONShaders(const std::string& relativePath)
{
	rapidjson::Document d = documentParse(std::move(relativePath));

	for (const auto& itShaders : d.GetArray())
	{
		std::string shaderName = itShaders.FindMember("name")->value.GetString();
		std::string shader_v = itShaders.FindMember("filePath_v")->value.GetString();
		std::string shader_f = itShaders.FindMember("filePath_f")->value.GetString();
		auto ShaderProgram = loadShaders(std::move(shaderName), std::move(shader_v), std::move(shader_f));

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(1080.f), 0.f, static_cast<float>(1080.f), -100.f, 100.f);
#ifdef OGL
		ShaderProgram->use();
		ShaderProgram->setInt("tex", 0);
		ShaderProgram->setMatrix4("projectionMat", projectionMatrix);
#endif
	}


	return true;
}

std::string ResourceManager::GetPath() { return m_path; }