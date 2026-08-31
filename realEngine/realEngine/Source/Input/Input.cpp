#include "Input.h"
#include "Backend/WindowHandling.h"
#include "Camera/Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

namespace Input {
	GLFWwindow* g_window = nullptr;
	float g_mousesensitivity = 0.1f;
	float g_cameraspeed = 1.0f;
	float g_deltatime = 0.0f;
	float m_lastframe = 0.0f;

	bool m_firstmouse = true;
	float m_lastx, m_lasty;
	float m_xoffset, m_yoffset;
	void (*m_processMouseMovementFunction_camera)(float, float, float);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
		float m_xpos = static_cast<float>(xpos);
		float m_ypos = static_cast<float>(ypos);
		if (m_firstmouse) {
			m_lastx = m_xpos;
			m_lasty = m_ypos;
			m_firstmouse = false;
		}

		m_xoffset = m_xpos - m_lastx;
		m_yoffset = m_lasty - m_ypos;

		m_lastx = m_xpos;
		m_lasty = m_ypos;

		m_processMouseMovementFunction_camera(m_xoffset, m_yoffset, g_mousesensitivity);
	}

	void Init(void* window, void (*ProcessMouseMovementFunction_camera)(float, float, float) ) {
		m_firstmouse = true;
		g_window = static_cast<GLFWwindow*>(window);
		m_processMouseMovementFunction_camera = ProcessMouseMovementFunction_camera;
		glfwSetCursorPosCallback(g_window, mouse_callback);
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Update() {
		float currentframe = static_cast<float>(glfwGetTime());
		g_deltatime = currentframe - m_lastframe;
		m_lastframe = currentframe;

		if (glfwGetKey(g_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			WindowHandling::Close();
		}	
		if (glfwGetKey(g_window, GLFW_KEY_W) == GLFW_PRESS) {
			Camera::MoveCamera(CameraMovement::FORWARD, g_cameraspeed * g_deltatime);
		}
		if (glfwGetKey(g_window, GLFW_KEY_S) == GLFW_PRESS) {
			Camera::MoveCamera(CameraMovement::BACKWARD, g_cameraspeed * g_deltatime);
		}
		if (glfwGetKey(g_window, GLFW_KEY_A) == GLFW_PRESS) {
			Camera::MoveCamera(CameraMovement::LEFT, g_cameraspeed * g_deltatime);
		}
		if (glfwGetKey(g_window, GLFW_KEY_D) == GLFW_PRESS) {
			Camera::MoveCamera(CameraMovement::RIGHT, g_cameraspeed * g_deltatime);
		}
	}
}