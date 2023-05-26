#include "ResourceManager.h"

#include "Serializer.h"

//#include "../Scene/Hierarchy.h"

#include "../GameTypes/GameObject.h"

#include "../../internal/Renderer/src/Renderer.h"
#include "Mesh.h"


//#include "../Renderer/AnimatedSprite.h"
//#include "../../../src/ScriptEngine.h"
#include "../../internal/UI/src/Panel.h"
#include "../../internal/UI/src/Button.h"
#include "../../internal/ComponentSystem/src/Transform.h"
#include "../../internal/ComponentSystem/src/LuaScript.h"

#include "../Helpers/casts.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>					 

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG

#include "stb_image.h"


std::unordered_map<std::string, std::unordered_map<std::string, Resource>> ResourceManager::m_resources = {};

std::queue<std::function<void(const std::string&, const std::string&, const std::string&)>> ResourceManager::shaderLoaders;
std::queue<std::tuple<std::string, std::string, std::string>> ResourceManager::shaderLoaderParameters;

//std::shared_ptr<std::pair<const std::string, std::function<void(const std::string)>>> ResourceManager::loader;
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

	Serializer::Init();
	size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}

void ResourceManager::UnloadAllResources()
{
	//TODO: Serializer::Serialize(m_path + "/res/scene.json");

	Serializer::Serialize(m_path + "/res/saves");

	m_resources.clear();
	//Hierarchy::Clear();
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

void ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	shaderLoaders.push(loadShaderProgram);
	shaderLoaderParameters.push({ shaderName, vertexPath, fragmentPath });
}

void ResourceManager::loadShaderProgram(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader!" << std::endl;
		system("pause");
		return;
	}
	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader!" << std::endl;
		system("pause");
		return;
	}

	makeResource<ShaderProgram>(shaderName, vertexPath, fragmentPath, vertexString, fragmentString);
}

void ResourceManager::loadShadersReal() {
	while (!shaderLoaders.empty()) {
		auto currentLoader = shaderLoaders.front();
		auto currentLoaderParameters = shaderLoaderParameters.front();

		std::apply(currentLoader, currentLoaderParameters);

		shaderLoaders.pop();
		shaderLoaderParameters.pop();
	}
}

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

	unsigned char* pixels = stbi_load(std::string(m_path + "/" + texturePath).c_str(), &width, &height, &channels, STBI_rgb_alpha);

	if (!pixels)
	{
		std::cerr << "Can't load image: " << texturePath << std::endl;
		system("pause");
		return nullptr;
	}

	auto texture = makeResource<Texture2D>(textureName, texturePath, width, height, channels, pixels, *getResource<SwapChain>("TestSwapChain"), *getResource<PhysicalDevice>("TestPhysicalDevice"), *getResource<LogicalDevice>("TestLogicalDevice"), *getResource<CommandPool>("TestCommandPool"));
	ResourceManager::getResource<Renderer>("main")->textures.push_back(texture);
	
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
	const std::string& meshName,
	const unsigned int spriteWidth,
	const unsigned int spriteHeight,
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


	return makeResource<Sprite>(spriteName, std::shared_ptr<GameObject>(nullptr), Texture, subTextureName, Shader,
		getResource<Mesh>(meshName), glm::vec3(0.f, 0.f, 1.0f), glm::vec3(1.f), glm::vec2(spriteWidth, spriteHeight));
}

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

	return makeResource<Mesh>(name, relativePath, std::move(vertices), std::move(indices));
}

bool ResourceManager::loadJSONScene(const std::string& relativePath)
{
	UnloadAllResources();
	rapidjson::Document d = documentParse(std::move(relativePath));

	loadJSONShaders(d.FindMember("shaders")->value.GetString());
	loadJSONTextureAtlasses(d.FindMember("textureAtlasses")->value.GetString());
	loadJSONTextures(d.FindMember("textures")->value.GetString());
	loadJSONSprites(d.FindMember("sprites")->value.GetString());
	loadJSONGameOjects(d.FindMember("GameObjects")->value.GetString());

	return true;
}

bool ResourceManager::loadSave(const std::string relativePath)
{
	//loader = std::make_shared<std::pair<const std::string, std::function<void(const std::string)>>>(relativePath, loadSaveReal);
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

	//loader = nullptr;
}

void ResourceManager::loadExecute()
{
	//if (loader)
	//	loader->second(loader->first);
}

std::vector<std::string> ResourceManager::getDirectories(const std::string& relativePath) {
	std::vector<std::string> directories;

	auto path = m_path + '/' + relativePath;
	for (auto& entry : std::filesystem::directory_iterator(path)) {
		auto absolute = Casts::wharTochar(entry.path().c_str());
		auto relative = Casts::wharTochar(std::filesystem::relative(absolute, path).c_str());
		directories.push_back({ relativePath + '/' + relative});
	}

	return directories;
}

[[nodiscard]]
bool ResourceManager::loadJSONGameOjects(const std::string& relativePath)
{
	auto directories = getDirectories(relativePath);

	std::unordered_map<std::string, std::vector<std::string>> gameObjectsChildren;

	for (size_t i = 0; i < directories.size(); ++i) {
		auto gameObjectFilename = std::filesystem::path{ directories[i] }.filename().string() + ".json";
		rapidjson::Document d = documentParse(directories[i] + '/' + gameObjectFilename);
		std::string name = d.FindMember("name")->value.GetString();
		std::shared_ptr<GameObject> gameObject = makeResource<GameObject>(name);



		std::unordered_map<std::string, std::vector<std::string>> components;
		std::vector<std::string> children;
		for (const auto& child : d.FindMember("children")->value.GetArray()) {
			children.push_back(child.GetString());


		}
		gameObjectsChildren.emplace(name, children);

		auto jsonComponents = d.FindMember("components")->value.GetObject();

		for (const auto& panel : jsonComponents.FindMember((Panel::type + 's').c_str())->value.GetArray()) {
			components[Panel::type].push_back(panel.FindMember("name")->value.GetString());


		}



		for (const auto& sprite : jsonComponents.FindMember((Sprite::type + 's').c_str())->value.GetArray()) {
			components[Sprite::type].push_back(sprite.FindMember("name")->value.GetString());


		}


		for (const auto& luascript : jsonComponents.FindMember((LuaScript::type + 's').c_str())->value.GetArray()) {
			components[Sprite::type].push_back(luascript.FindMember("name")->value.GetString());
		}

		for (const auto& transform : jsonComponents.FindMember((Transform::type + 's').c_str())->value.GetArray()) {


			components[Sprite::type].push_back(transform.FindMember("name")->value.GetString());
		}

		const std::string panelsDirectoryPath = directories[i] + "/Components/" + Panel::type + 's';
		const std::string scriptsDirectoryPath = directories[i] + "/Components/" + LuaScript::type + 's';
		const std::string spritesDirectoryPath = directories[i] + "/Components/" + Sprite::type + 's';
		const std::string transformsDirectoryPath = directories[i] + "/Components/" + Transform::type + 's';
		const std::string colliderDirectoryPath = directories[i] + "/Components/" + Collider2D::type + 's';

		auto panelDirectories = getDirectories(panelsDirectoryPath);
		for (size_t i = 0; i < panelDirectories.size(); ++i) {
			auto panelFilename = std::filesystem::path{ panelDirectories[i] }.filename().string() + ".json";

			rapidjson::Document panelDocument = documentParse(panelDirectories[i] + '/' + panelFilename);

			auto panelName = panelDocument.FindMember("name")->value.GetString();
			std::shared_ptr<Panel> panel = makeResource<Panel>(panelName);
			gameObject->addComponent<Panel>(panel);
			auto uis = panelDocument.FindMember("uis")->value.GetObject();
			auto jsonButtons = uis.FindMember(std::string(Button::type + 's').c_str());

			for (const auto& button : jsonButtons->value.GetArray()) {
				panel->addChild(std::make_shared<Button>(button.FindMember("name")->value.GetString()));
				//TODO: additional settings could be added by reading "Buttons" subdirectory
			}
		}

		auto spriteDirectories = getDirectories(spritesDirectoryPath);
		for (size_t i = 0; i < spriteDirectories.size(); ++i) {
			auto spriteFilename = std::filesystem::path{ spriteDirectories[i] }.filename().string() + ".json";

			rapidjson::Document spriteDocument = documentParse(spriteDirectories[i] + '/' + spriteFilename);

			std::string spriteName = spriteDocument.FindMember("name")->value.GetString();
			std::string textureName = spriteDocument.FindMember("textureName")->value.GetString();
			std::string shaderProgramName = spriteDocument.FindMember("shaderProgramName")->value.GetString();
			std::string meshName = spriteDocument.FindMember("meshName")->value.GetString();
			float width = spriteDocument.FindMember("width")->value.GetFloat();
			float height = spriteDocument.FindMember("height")->value.GetFloat();
			std::string subTextureName = spriteDocument.FindMember("subTextureName")->value.GetString();

			//TODO: for additional settings you could implement sprite settings loading by sprite name

			auto textureDocument = documentParse(spriteDirectories[i] + '/' + textureName + ".json");
			auto shaderDocument = documentParse(spriteDirectories[i] + '/' + shaderProgramName + ".json");
			auto meshDocument = documentParse(spriteDirectories[i] + '/' + meshName + ".json");

			ResourceManager::loadShaders(shaderDocument.FindMember("name")->value.GetString(), shaderDocument.FindMember("vertexPath")->value.GetString(), shaderDocument.FindMember("fragmentPath")->value.GetString());
			auto shaderProgram = getResource<ShaderProgram>(shaderProgramName);
			auto texture = loadTexture(textureName, textureDocument.FindMember("path")->value.GetString());
			auto mesh = ResourceManager::loadMesh(meshName, meshDocument.FindMember("path")->value.GetString());
			gameObject->addComponent<Sprite>(ResourceManager::loadSprite(spriteName, textureName, shaderProgramName, meshName, width, height, subTextureName));
		}

		auto scriptDirectories = getDirectories(scriptsDirectoryPath);
		for (size_t i = 0; i < scriptDirectories.size(); ++i) {
			auto scriptFilename = std::filesystem::path{ scriptDirectories[i] }.filename().string() + ".json";

			rapidjson::Document scriptDocument = documentParse(spriteDirectories[i] + '/' + scriptFilename);

			auto scriptName = scriptDocument.FindMember("name")->value.GetString();
			auto scriptPath = scriptDocument.FindMember("path")->value.GetString();

			gameObject->addComponent<LuaScript>(std::make_shared<LuaScript>(scriptName, scriptPath, L));
		}

		auto transformDirectories = getDirectories(transformsDirectoryPath);
		for (size_t i = 0; i < transformDirectories.size(); ++i) {
			auto transformFilename = std::filesystem::path{ transformDirectories[i] }.filename().string() + ".json";

			gameObject->addComponent<Transform>(loadJSONTransform(transformDirectories[i] + '/' + transformFilename));
		}

		auto colliderDirectories = getDirectories(colliderDirectoryPath);
		for (size_t i = 0; i < colliderDirectories.size(); ++i) {
			auto colliderFilename = std::filesystem::path{ colliderDirectories[i] }.filename().string() + ".json";

			rapidjson::Document colliderDocument = documentParse(colliderDirectories[i] + '/' + colliderFilename);

			auto colliderName = colliderDocument.FindMember("name")->value.GetString();

			std::shared_ptr<Transform> transform = loadJSONTransform(colliderDirectories[i] + '/' + colliderDocument.FindMember(Transform::type.c_str())->value.GetString() + ".json");

			gameObject->addComponent<Collider2D>(makeResource<Collider2D>(colliderName, transform));
		}
	}



	return true;
}

std::shared_ptr<Transform> ResourceManager::loadJSONTransform(const std::string& path) {
	rapidjson::Document transformDocument = documentParse(path);

	auto transformName = transformDocument.FindMember("name")->value.GetString();
	auto transformPosition = transformDocument.FindMember("position")->value.GetArray();
	auto transformRotation = transformDocument.FindMember("rotation")->value.GetArray();
	auto transformScale = transformDocument.FindMember("scale")->value.GetArray();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	size_t j = 0;
	for (auto& arg : transformPosition) {
		position[j] = arg.GetFloat();
		++j;
	}
	j = 0;
	for (auto& arg : transformRotation) {
		rotation[j] = arg.GetFloat();
		++j;
	}
	j = 0;
	for (auto& arg : transformScale) {
		scale[j] = arg.GetFloat();
		++j;
	}

	return std::make_shared<Transform>(position, rotation, scale, transformName);
}

void ResourceManager::loadJSONComponents(const rapidjson::Value& it, std::shared_ptr<GameObject> gameObject)
{
	std::unordered_map<std::string, ComponentView> components;
	if (it.FindMember("Components")->value.IsArray())
	{
		for (const auto& itComponents : it.FindMember("Components")->value.GetArray())
		{
			std::string type = itComponents.FindMember("type")->value.GetString();
			if (type == "LuaScript")
			{
				gameObject->addComponent<LuaScript>(std::make_shared<LuaScript>(itComponents.FindMember("name")->value.GetString(), itComponents.FindMember("path")->value.GetString(), L));
			}
			else if (type == "Button")
			{
				gameObject->addComponent<Button>(std::make_shared<Button>(itComponents.FindMember("name")->value.GetString()));
			}
		}
	}
}

bool ResourceManager::loadJSONSprites(const std::string& relativePath) //correct
{
	rapidjson::Document d = documentParse(std::move(relativePath));

	auto it = d.Begin();

	while (it != d.End())
	{
		const std::string spriteName = it->FindMember("spriteName")->value.GetString();
		const std::string textureName = it->FindMember("textureName")->value.GetString();
		const std::string shaderName = it->FindMember("shaderName")->value.GetString();
		const std::string meshName = it->FindMember("meshName")->value.GetString();
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
#endif



		loadSprite(spriteName, textureName, shaderName, meshName, static_cast<uint32_t>(spriteSize.x), static_cast<uint32_t>(spriteSize.y), subTextureName);

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
		loadTexture(Name, path);
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
		loadShaders(std::move(shaderName), std::move(shader_v), std::move(shader_f));

#ifdef OGL
		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(1080.f), 0.f, static_cast<float>(1080.f), -100.f, 100.f);

		ShaderProgram->use();
		ShaderProgram->setInt("tex", 0);
		ShaderProgram->setMatrix4("projectionMat", projectionMatrix);
#endif
	}


	return true;
}

std::string ResourceManager::GetPath() { return m_path; }