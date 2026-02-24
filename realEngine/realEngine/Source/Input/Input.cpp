#include "Input.h"
#include "../Backend/WindowHandling.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>

namespace Input {
	GLFWwindow* g_window = nullptr;
	float g_mousesensitivity = 0.1f;

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

	void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			WindowHandling::Close();
		}
	}
	void Init(void* window, void (*ProcessMouseMovementFunction_camera)(float, float, float) ) {
		m_firstmouse = true;
		g_window = static_cast<GLFWwindow*>(window);
		m_processMouseMovementFunction_camera = ProcessMouseMovementFunction_camera;
		glfwSetKeyCallback(g_window, keyboard_callback);
		glfwSetCursorPosCallback(g_window, mouse_callback);
		glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	void Update() {
		// TEMP - Find out what to put here lol
	}
}