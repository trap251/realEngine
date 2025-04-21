#include "Input.h"
#include <GLFW/glfw3.h>

namespace Input {
	GLFWwindow* g_window = NULL;
	void Init(void* window) {
		g_window = static_cast<GLFWwindow*>(window);
	}
	void Update() {
		//update
	}
}