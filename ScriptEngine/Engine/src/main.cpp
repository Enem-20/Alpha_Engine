
#include "../internal/Renderer/src/Renderer.h"
#include "Resources/ResourceManager.h"
#include "../internal/Renderer/src/ImGui/ImGui.h"
#include "GameTypes/GameObject.h"
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

	//auto texture = ResourceManager::loadTexture("Desk", "Desk.png");

	auto sprite = ResourceManager::loadSprite("DeskSprite", "Desk", "TestShaderProgram", ResourceManager::getResource<Texture2D>("Desk")->getWidth(), ResourceManager::getResource<Texture2D>("Desk")->getHeight(), 0, "default");

	auto transform = std::make_shared<Transform>(glm::vec3(0.f), glm::vec3(0.f), glm::vec3(1.f), "Desk");
	auto button = std::make_shared<Button>("Button");
	std::unordered_map <std::string, ComponentView> components;
	//components.emplace("Desk", ComponentView{ std::reinterpret_pointer_cast<void>(sprite)});
	//components.emplace("Desk", ComponentView{ std::reinterpret_pointer_cast<void>(transform) });


	auto gameObject = ResourceManager::makeResource<GameObject>("Desk", transform, sprite, components);
	//gameObject->Scale(glm::vec3(-900.f, -900.f, 0.f));
	gameObject->addComponent<Button>(button->name,button);
	//sprite->setSize({ 135.f, 135.f });
	WindowManager::GetCurrentWindow()->AddUI(button);
	renderer->render();

	ResourceManager::UnloadAllResources();

	gameObject.reset();
	transform.reset();
	sprite.reset();
	button.reset();
	
	ImGuiManager::destroy();
	renderer.reset();
	return 0;
}