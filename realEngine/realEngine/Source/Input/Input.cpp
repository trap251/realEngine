#include "Input.h"
#include "../Backend/WindowHandling.h"
#include <GLFW/glfw3.h>
#include <iostream>


namespace Input {
	GLFWwindow* g_window = nullptr;
	void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	}

	void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			WindowHandling::Close();
		}
	}
	void Init(void* window) {
		g_window = static_cast<GLFWwindow*>(window);
		glfwSetKeyCallback(g_window, keyboard_callback);
		glfwSetCursorPosCallback(g_window, mouse_callback);


	}
	void Update() {
		WindowHandling::PollEvents();
	}
}