//Test cpp file

#include "../internal/Renderer/src/Renderer.h"
#include "Resources/ResourceManager.h"
#include "../internal/Renderer/src/ImGui/ImGui.h"
#include "GameTypes/GameObject.h"
#include "../internal/UI/src/Panel.h"
#include "../internal/UI/src/Button.h"
#include "../internal/ComponentSystem/src/Transform.h"
#include "../internal/Renderer/src/Texture2D.h"
#include "../internal/Renderer/src/WindowManager.h"

#include <iostream>
#include <unordered_map>
#include <string>


int main(int argc, char** argv) {
	ResourceManager::SetExecutablePath(argv[0]);

#ifdef GLFW_INCLUDE_VULKAN
	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
#endif
	ImGuiManager::init();
	auto sprite = ResourceManager::loadSprite("DeskSprite", "Desk", "TestShaderProgram", ResourceManager::getResource<Texture2D>("Desk")->getWidth(), ResourceManager::getResource<Texture2D>("Desk")->getHeight(), 0, "default");
	auto another = ResourceManager::loadSprite("AnotherSprite", "Another", "TestShaderProgram", ResourceManager::getResource<Texture2D>("Another")->getWidth(), ResourceManager::getResource<Texture2D>("Another")->getHeight(), 0, "default");
	sprite->setPosition(glm::vec3(0.0f,0.0f, 0.1f));
	auto transform = std::make_shared<Transform>(glm::vec3(0.f, 0.0f, 1.0f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 1.f), "Desk");
	auto transform2 = std::make_shared<Transform>(glm::vec3(0.f, 0.2f, 0.5f), glm::vec3(0.f), glm::vec3(0.125f, 0.125f, 1.0f), "Another");
	auto button = std::make_shared<Button>("Button");
	auto button2 = std::make_shared<Button>("Button2");
	auto panel = ResourceManager::makeResource<Panel>("panel");
	//components.emplace("Desk", ComponentView{ std::reinterpret_pointer_cast<void>(sprite)});
	//components.emplace("Desk", ComponentView{ std::reinterpret_pointer_cast<void>(transform) });


	auto gameObject = ResourceManager::makeResource<GameObject>("Desk");
	auto gameObject2 = ResourceManager::makeResource<GameObject>("Another");

	gameObject->addComponent<Transform>(transform);
	gameObject->addComponent<Sprite>(sprite);
	gameObject->addComponent<Panel>(panel);
	gameObject->addComponent<Button>(button);
	gameObject->addComponent<Button>(button2);

	gameObject2->addComponent<Transform>(transform2);
	gameObject2->addComponent<Sprite>(another);

	panel->addChild(button);
	panel->addChild(button2);
	renderer->render();

	ResourceManager::UnloadAllResources();

	gameObject2.reset();
	gameObject.reset();
	sprite.reset();
	another.reset();
	panel.reset();
	button.reset();
	button2.reset();
	transform.reset();
	transform2.reset();
	
	ImGuiManager::destroy();
	renderer.reset();
	return 0;
}