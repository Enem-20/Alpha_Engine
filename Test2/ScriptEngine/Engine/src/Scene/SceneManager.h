#pragma once

#include <string>

class SceneManager
{
public:
	static void Awake(std::string dir);
	static void Start();
	static void Update();
	static void FixedUpdate();

	static void LoadScene(std::string Scene);
private:
};