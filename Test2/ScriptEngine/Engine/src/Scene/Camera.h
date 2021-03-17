#pragma once

#include <glm/vec3.hpp>

class Camera
{
public:
	Camera() = default;

	glm::vec3 position;
private:
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
};