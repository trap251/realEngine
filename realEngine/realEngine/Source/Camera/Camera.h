#pragma once
// TEMP - Find out if this is normal and if there is a way to get rid of this. 
#include <glm/glm.hpp>

namespace Camera {
	//TEMP - Remove hardcoded values
	void Init(glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 camera_up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0);
	void ProcessMouseMovement(float xoffset, float yoffset, float sensitivity);
	glm::mat4 GetViewMatrix();
}