#include "Scene.h"

Scene* Scene::GetInstance()
{
	if (!scene)
	{
		return scene = new Scene;
	}

	return scene;
}