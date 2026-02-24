#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace Camera {
	// TEMP - Default global values

	float g_yaw = -90.0f;
	float g_pitch = 0;
	float g_speed = 2.5f;
	float g_zoom = 45.0f;

	glm::vec3 g_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 g_front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 g_up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 g_worldup = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 g_right = glm::vec3(0);

	void UpdateVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(g_yaw)) * cos(glm::radians(g_pitch));
		front.y = sin(glm::radians(g_pitch));
		front.z = sin(glm::radians(g_yaw)) * cos(glm::radians(g_pitch));

		g_front = glm::normalize(front);

		g_right = glm::normalize(glm::cross(g_front, g_worldup));
		g_up = glm::normalize(glm::cross(g_right, g_front));
	}

	void Init(glm::vec3 camera_position, glm::vec3 camera_up, float yaw, float pitch) {
		g_position = camera_position;
		g_up = camera_up;
		g_yaw = yaw;
		g_pitch = pitch;
		UpdateVectors();
	}

	void ProcessMouseMovement(float xoffset, float yoffset, float sensitivity) {
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		g_yaw += xoffset;
		g_pitch += yoffset;

		if (g_pitch > 89.0f) g_pitch = 89.0f;
		if (g_pitch < -89.0f) g_pitch = -89.0f;
		UpdateVectors();
	}
	glm::mat4 GetViewMatrix() {
		return glm::lookAt(g_position, g_position + g_front, g_up);
	}
	
}