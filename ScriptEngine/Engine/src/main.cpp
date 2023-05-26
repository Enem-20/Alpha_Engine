//Test cpp file

#include "../internal/Renderer/src/Renderer.h"
#include "Resources/ResourceManager.h"
#include "../internal/Input/src/Input.h"
#include "../internal/Renderer/src/ImGui/ImGui.h"
#include "GameTypes/GameObject.h"
#include "../internal/Physics/src/Raycast.h"
#include "../internal/ComponentSystem/src/Collider2D.h"
#include "../internal/UI/src/Panel.h"
#include "../internal/UI/src/Button.h"
#include "../internal/ComponentSystem/src/Transform.h"
#include "../internal/Renderer/src/Texture2D.h"
#include "../internal/Renderer/src/WindowManager.h"

#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>


int main(int argc, char** argv) {
	ResourceManager::SetExecutablePath(argv[0]);

	ResourceManager::loadShaders("TestShaderProgram", "vert.spv", "frag.spv");
#ifdef GLFW_INCLUDE_VULKAN
	std::shared_ptr<Renderer> renderer = ResourceManager::makeResource<Renderer>("main");
#endif
	{
		Input::init();
		ImGuiManager::init();

		ResourceManager::loadJSONGameOjects("res/saves/GameObjects");

		/*ResourceManager::loadTexture("Desk", "Desk.png");
		ResourceManager::loadTexture("Another", "Another.png");
		auto mesh = ResourceManager::loadMesh("SpriteMesh", "SpriteMesh.obj");
		auto sprite = ResourceManager::loadSprite("DeskSprite", "Desk", "TestShaderProgram", "SpriteMesh", ResourceManager::getResource<Texture2D>("Desk")->getWidth(), ResourceManager::getResource<Texture2D>("Desk")->getHeight(), "default");
		auto another = ResourceManager::loadSprite("AnotherSprite", "Another", "TestShaderProgram", "SpriteMesh", ResourceManager::getResource<Texture2D>("Another")->getWidth(), ResourceManager::getResource<Texture2D>("Another")->getHeight(), "default");

		auto transform = std::make_shared<Transform>(glm::vec3(0.f, 0.0f, 20.0f), glm::vec3(0.f), glm::vec3(1.f, 1.f, 0.01f), "Desk");
		auto transform2 = std::make_shared<Transform>(glm::vec3(0.0f, 0.0f, 10.0f), glm::vec3(0.f), glm::vec3(0.125f, 0.125f, 0.01f), "Another");
		auto button = std::make_shared<Button>("Button");
		auto button2 = std::make_shared<Button>("Button2");
		auto panel = ResourceManager::makeResource<Panel>("panel");


		auto collider = ResourceManager::makeResource<Collider2D>("Desk", transform);
		auto collider2 = ResourceManager::makeResource<Collider2D>("Another", transform2);

		auto gameObject = ResourceManager::makeResource<GameObject>("Desk");
		auto gameObject2 = ResourceManager::makeResource<GameObject>("Another");

		gameObject->addComponent<Transform>(transform);
		gameObject->addComponent<Sprite>(sprite);
		gameObject->addComponent<Panel>(panel);
		gameObject->addComponent<Collider2D>(collider);

		gameObject2->addComponent<Transform>(transform2);
		gameObject2->addComponent<Sprite>(another);
		gameObject2->addComponent<Collider2D>(collider2);

		panel->addChild(button);
		panel->addChild(button2);*/

		Raycast raycast;



		auto hittedCollider = raycast.closestBodyHit(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 50.0f));

		if (hittedCollider) {
			std::cout << "Hitted collider: " << hittedCollider->name << '\n';
		}
		renderer->render();

		ResourceManager::UnloadAllResources();
	}

	ImGuiManager::destroy();
	renderer.reset();
	return 0;
}