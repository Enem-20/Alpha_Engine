#include "Serializer.h"

#include "ResourceManager.h"

#include "Mesh.h"

#include "../GameTypes/GameObject.h"

#include "../../internal/ComponentSystem/src/Collider2D.h"
#include "../../internal/Renderer/src/Sprite.h"
#include "../../internal/Renderer/src/Texture2D.h"
#include "../../internal/UI/src/Panel.h"
#include "../../internal/UI/src/Button.h"
#include "../../internal/ComponentSystem/src/Transform.h"
#include "../../internal/ComponentSystem/src/LuaScript.h"

#include "../../internal/ComponentSystem/src/Component.h"

#include <fstream>
#include <functional>
#include <filesystem>

#include <glm/glm.hpp>

template<class ComponentType>
void RecordAnyComponentInfo(std::shared_ptr<ComponentType> component, prettywriter* writer) {
	static_assert(std::is_base_of_v<Component, ComponentType>, "isn't derived from Component");
	writer->Key("type");
	writer->String(ComponentType::type.c_str());
	writer->Key("name");
	writer->String(component->name.c_str());
}

template<class UIType>
const rapidjson::StringBuffer RecordUIInfoFromPanel(std::shared_ptr<UIType> ui, prettywriter* writer) {
	static_assert(std::is_base_of_v<UIelement, UIType>, "isn't derived from UIelement");

	writer->Key("type");
	writer->String(UIType::type.c_str());
	writer->Key("name");
	writer->String(ui->name.c_str());
}

template<class R,class ... Args>
void SerializeInSubdirectory(const std::string& path, std::function<R(Args...)>& serializeInSubdirectoryFunction, Args... args) {
	std::string directory = "";
	const size_t last_slash_idx = path.rfind('/');
	if (std::string::npos != last_slash_idx)
	{
		directory = path.substr(0, last_slash_idx);
	}
	
	if(!std::filesystem::exists(directory))
		std::filesystem::create_directory(directory);

	std::ofstream f(path);

	rapidjson::StringBuffer buffer = serializeInSubdirectoryFunction(args...);
	buffer.Flush();
	auto string = buffer.GetString();

	f << string;
	f.flush();
	f.close();
}

void CreateSubDirectories(const std::string& root, const std::vector<std::string> newDirectoryNames) {
	for (auto directoryName : newDirectoryNames) {
		if(!std::filesystem::exists(root + '/' + directoryName))
			std::filesystem::create_directory(root + '/' + directoryName);
	}
}

void Serializer::Serialize(const std::string& directory)
{
	const std::string gameObjectsDirectory = directory + '/' + GameObject::type + 's';
	std::filesystem::create_directories(gameObjectsDirectory);

	auto gameObjects = ResourceManager::getResourcesWithType<GameObject>();

	for (auto gameObject : *gameObjects) {
		const std::string gameObjectDirectory = gameObjectsDirectory + '/' + gameObject.second.getResource<GameObject>()->name;
		auto gameObjectSerializer = std::function<rapidjson::StringBuffer()>([&](){
			rapidjson::StringBuffer sb;

			prettywriter writer(sb);

			writer.StartObject();

			writer.Key("name");
			writer.String(gameObject.second.getResource<GameObject>()->name.c_str());

			writer.Key("children");
			writer.StartArray();

			for (auto child : gameObject.second.getResource<GameObject>()->children) {
				writer.Key("name");
				writer.String(child->name.c_str());
			}			

			writer.EndArray();

			writer.Key("components");
			writer.StartObject();

			const std::string componentsDirectory = gameObjectDirectory + '/' + "Components";
			if(!std::filesystem::exists(componentsDirectory))
			std::filesystem::create_directory(componentsDirectory);

			const std::string panelsDirectory = componentsDirectory + '/' + Panel::type + 's';
			const std::string spritesDirectory = componentsDirectory + '/' + Sprite::type + 's';
			const std::string scriptsDirectory = componentsDirectory + '/' + LuaScript::type + 's';
			const std::string transformsDirectory = componentsDirectory + '/' + Transform::type + 's';
			const std::string collider2DsDirectory = componentsDirectory + '/' + Collider2D::type + 's';

			std::vector<std::string> compDirs = { Panel::type + 's', Sprite::type + 's', LuaScript::type + 's', Transform::type + 's', Collider2D::type + 's'};

			CreateSubDirectories(componentsDirectory, compDirs);

			writer.Key((Panel::type + 's').c_str());
			writer.StartArray();
			auto panels = gameObject.second.getResource<GameObject>()->getComponentsWithType<Panel>();
			if(panels)
				for (auto panelIt : *panels) {
				const std::string panelDirectory = panelsDirectory + '/' + panelIt.second.getComponentFromView<Panel>()->name;
				
				writer.StartObject();

				writer.Key("name");
				writer.String(panelIt.second.getComponentFromView<Panel>()->name.c_str());

				writer.EndObject();

				auto panelSerializer = std::function<rapidjson::StringBuffer()>([&]() {
					rapidjson::StringBuffer sb;

					prettywriter writer(sb);
					
					writer.StartObject();

					writer.Key("name");
					writer.String(panelIt.second.getComponentFromView<Panel>()->name.c_str());

					writer.Key("uis");
					writer.StartObject();

					writer.Key((Button::type + 's').c_str());
					writer.StartArray();

					const std::string buttonsDirectory = panelDirectory + '/' + Button::type + 's';

					std::vector<std::string> uiDirs = { Button::type + 's' };

					CreateSubDirectories(panelDirectory, uiDirs);

					auto buttons = panelIt.second.getComponentFromView<Panel>()->getChildrenWithType<Button>();

					for (auto buttonIt : *buttons) {
						writer.StartObject();

						writer.Key("name");
						writer.String(buttonIt.second.getUIFromView<Button>()->name.c_str());

						
						//writer.Key("type");
						//writer.String(Button::type.c_str());

						writer.EndObject();

						auto buttonDirectory = buttonsDirectory + '/' + buttonIt.second.getUIFromView<Button>()->name.c_str();

						auto buttonSerializer = std::function<rapidjson::StringBuffer()>([&]() {
							rapidjson::StringBuffer sb;

							prettywriter writer(sb);

							writer.StartObject();

							writer.Key("name");
							writer.String(buttonIt.second.getUIFromView<Button>()->name.c_str());


							writer.Key("type");
							writer.String(std::string(Button::type + 's').c_str());

							writer.EndObject();

							return sb;
						});

						SerializeInSubdirectory(buttonDirectory + '/' + buttonIt.second.getUIFromView<Button>()->name.c_str() + ".json", buttonSerializer);
					}

					writer.EndArray();

					writer.EndObject();

					writer.EndObject();


					return sb;
				});


				SerializeInSubdirectory(panelDirectory + '/' + panelIt.second.getComponentFromView<Panel>()->name.c_str() + ".json", panelSerializer);
			}
			writer.EndArray();

			writer.Key((Sprite::type + 's').c_str());
			writer.StartArray();
			auto sprites = gameObject.second.getResource<GameObject>()->getComponentsWithType<Sprite>();
			if(sprites)
				for (auto spriteIt : *sprites) {
				const std::string spriteDirectory = spritesDirectory + '/' + spriteIt.second.getComponentFromView<Sprite>()->name;

				writer.StartObject();

				writer.Key("name");
				writer.String(spriteIt.second.getComponentFromView<Sprite>()->name.c_str());

				writer.EndObject();

				auto spriteSerializer = std::function<rapidjson::StringBuffer()>([&]() {
					rapidjson::StringBuffer sb;

					prettywriter writer(sb);

					auto sprite = spriteIt.second.getComponentFromView<Sprite>();

					writer.StartObject();

					writer.Key("name");
					writer.String(sprite->name.c_str());
					writer.Key("textureName");
					writer.String(sprite->getTexture()->name.c_str());
					writer.Key("shaderProgramName");
					writer.String(sprite->getShaderProgram()->name.c_str());
					writer.Key("meshName");
					writer.String(sprite->getMesh()->name.c_str());
					writer.Key("width");
					writer.Double(sprite->getSize().x);
					writer.Key("height");
					writer.Double(sprite->getSize().y);
					writer.Key("subTextureName");
					writer.String(sprite->getSubTextureName().c_str());

					writer.EndObject();

					return sb;
				});

				SerializeInSubdirectory(spriteDirectory + '/' + spriteIt.second.getComponentFromView<Sprite>()->name + ".json", spriteSerializer);

				{
					auto textureName = spriteIt.second.getComponentFromView<Sprite>()->getTexture()->name;

					auto texturePath = spriteDirectory + '/' + textureName + ".json";

					rapidjson::StringBuffer sb;

					prettywriter writer(sb);

					writer.StartObject();

					writer.Key("name");
					writer.String(textureName.c_str());
					writer.Key("path");
					writer.String(spriteIt.second.getComponentFromView<Sprite>()->getTexture()->m_path.c_str());

					writer.EndObject();

					std::ofstream f(texturePath);

					f << sb.GetString();

					f.flush();
					f.close();
				}
				{
					auto shaderName = spriteIt.second.getComponentFromView<Sprite>()->getShaderProgram()->name;

					auto shaderPath = spriteDirectory + '/' + shaderName + ".json";

					rapidjson::StringBuffer sb;

					prettywriter writer(sb);

					writer.StartObject();

					writer.Key("name");
					writer.String(shaderName.c_str());
					writer.Key("vertexPath");
					writer.String(spriteIt.second.getComponentFromView<Sprite>()->getShaderProgram()->vertexShaderPath.c_str());
					writer.Key("fragmentPath");
					writer.String(spriteIt.second.getComponentFromView<Sprite>()->getShaderProgram()->fragmentShaderPath.c_str());

					writer.EndObject();

					std::ofstream f(shaderPath);

					f << sb.GetString();

					f.flush();
					f.close();
				}
				{
					auto meshName = spriteIt.second.getComponentFromView<Sprite>()->getMesh()->name;

					auto meshPath = spriteDirectory + '/' + meshName + ".json";

					rapidjson::StringBuffer sb;

					prettywriter writer(sb);

					writer.StartObject();

					writer.Key("name");
					writer.String(meshName.c_str());
					writer.Key("path");
					writer.String(spriteIt.second.getComponentFromView<Sprite>()->getMesh()->path.c_str());

					writer.EndObject();

					std::ofstream f(meshPath);

					f << sb.GetString();

					f.flush();
					f.close();
				}
			}
			writer.EndArray();

			writer.Key((LuaScript::type + 's').c_str());
			writer.StartArray();
			auto scripts = gameObject.second.getResource<GameObject>()->getComponentsWithType<LuaScript>();
			if(scripts)
				for (auto scriptIt : *scripts) {
				const std::string scriptDirectory = scriptsDirectory + '/' + scriptIt.second.getComponentFromView<LuaScript>()->name;
				
				writer.StartObject();
				writer.Key("name");
				writer.String(scriptIt.second.getComponentFromView<LuaScript>()->name.c_str());
				writer.EndObject();

				auto scriptSerializer = std::function<rapidjson::StringBuffer()>([&]() {
					rapidjson::StringBuffer sb;

					prettywriter writer(sb);

					writer.StartObject();

					writer.Key("name");
					writer.String(scriptIt.second.getComponentFromView<LuaScript>()->name.c_str());
					writer.Key("path");
					writer.String(scriptIt.second.getComponentFromView<LuaScript>()->m_path.c_str());

					writer.EndObject();

					return sb;
				});

				SerializeInSubdirectory(scriptDirectory + '/' + scriptIt.second.getComponentFromView<LuaScript>()->name + ".json", scriptSerializer);
			}
			writer.EndArray();

			writer.Key((Transform::type + 's').c_str());
			writer.StartArray();
			auto transforms = gameObject.second.getResource<GameObject>()->getComponentsWithType<Transform>();
			if(transforms)
				for (auto transformIt : *transforms) {
				const std::string transformDirectory = transformsDirectory + '/' + transformIt.second.getComponentFromView<Transform>()->name;
				
				writer.StartObject();

				writer.Key("name");
				writer.String(transformIt.second.getComponentFromView<Transform>()->name.c_str());

				writer.EndObject();

				auto transformSerializer = std::function<rapidjson::StringBuffer()>([&]() {
					rapidjson::StringBuffer sb;

					prettywriter writer(sb);

					Serialize(transformIt.second.getComponentFromView<Transform>(), &writer, transformIt.second.getComponentFromView<Transform>()->name);

					return sb;
				});

				SerializeInSubdirectory(transformDirectory + '/' + transformIt.second.getComponentFromView<Transform>()->name + ".json", transformSerializer);
			}
			writer.EndArray();

			writer.Key((Collider2D::type + 's').c_str());
			writer.StartArray();
			auto collider2Ds = gameObject.second.getResource<GameObject>()->getComponentsWithType<Collider2D>();
			if(collider2Ds)
				for (auto colliderIt : *collider2Ds) {
					const std::string colliderDirectory = collider2DsDirectory + '/' + colliderIt.second.getComponentFromView<Collider2D>()->name;

					writer.StartObject();

					writer.Key("name");
					writer.String(colliderIt.second.getComponentFromView<Collider2D>()->name.c_str());

					writer.EndObject();

					auto colliderSerializer = std::function<rapidjson::StringBuffer()>([&]() {
						rapidjson::StringBuffer sb;

						prettywriter writer(sb);

						writer.StartObject();

						writer.Key("name");
						writer.String(colliderIt.second.getComponentFromView<Collider2D>()->name.c_str());
						writer.Key(Transform::type.c_str());
						writer.String(Transform::type.c_str());

						writer.EndObject();

						return sb;
					});

					auto colliderTransformSerializer = std::function<rapidjson::StringBuffer()>([&]() {
						rapidjson::StringBuffer sb;

						prettywriter writer(sb);

						auto transform = colliderIt.second.getComponentFromView<Collider2D>()->getTransform();
						Serialize(transform, &writer);

						return sb;
					});

					SerializeInSubdirectory(colliderDirectory + '/' + colliderIt.second.getComponentFromView<Collider2D>()->name.c_str() + ".json", colliderSerializer);
					SerializeInSubdirectory(colliderDirectory + '/' + Transform::type + ".json", colliderTransformSerializer);
				}
			writer.EndArray();

			writer.EndObject();
			writer.EndObject();

			return sb;
		});

		SerializeInSubdirectory(gameObjectDirectory + '/' + gameObject.second.getResource<GameObject>()->name + ".json", gameObjectSerializer);
	}
}

void Serializer::Serialize(std::shared_ptr<Transform> transform, prettywriter* writer, std::string name, std::string path) {

	writer->StartObject();

	writer->Key("name");
	if (name != "")
		writer->String(name.c_str());
	else
		writer->String(Transform::type.c_str());

	Serialize(transform->GetPosition(), writer, "position");
	Serialize(transform->GetRotation(), writer, "rotation");
	Serialize(transform->GetScale(), writer, "scale");

	writer->EndObject();
}

const rapidjson::StringBuffer  Serializer::Serialize(glm::ivec2 _ivec2, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}

	//Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 2; ++i)
	{
		writer->Double(_ivec2[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::vec2   _vec2, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	//Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 2; ++i)
	{
		writer->Double(_vec2[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::ivec3 _ivec3, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	//Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 3; ++i)
	{
		writer->Int(_ivec3[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::vec3   _vec3, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	//Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 3; ++i)
	{
		writer->Double(_vec3[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::ivec4 _ivec4, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	//Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 4; ++i)
	{
		writer->Int(_ivec4[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::vec4   _vec4, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	//Write write(path, &sb);

	writer->StartArray();

	for (size_t i = 0; i < 4; ++i)
	{
		writer->Double(_vec4[i]);
	}

	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::mat3   _mat3, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	//Write write(path, &sb);

	writer->StartArray();
	for (size_t i = 0; i < 3; ++i)
	{
		Serialize(_mat3[i], writer, "vec4");
	}
	writer->EndArray();

	return sb;
}
const rapidjson::StringBuffer  Serializer::Serialize(glm::mat4   _mat4, prettywriter* writer, std::string name, std::string path)
{
	rapidjson::StringBuffer sb;

	if (writer && name != "")
	{
		writer->Key(name.c_str());
	}
	else
	{
		writer = new prettywriter(sb);
	}
	//Write write(path, &sb);

	writer->StartArray();
	for (size_t i = 0; i < 4; ++i)
	{
		Serialize(_mat4[i], writer, "vec4");
	}
	writer->EndArray();

	return sb;
}