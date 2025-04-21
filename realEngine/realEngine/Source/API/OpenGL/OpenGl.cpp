#include <glad/glad.h>

#include "OpenGL.h"
#include "Backend/WindowHandling.h"
#include <iostream>

namespace OpenGL {
	void Init()
	{
		WindowHandling::MakeContextCurrent();
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to load GLAD\n";
			return;
		}
	}
	void Viewport(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	void Clear() {
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}