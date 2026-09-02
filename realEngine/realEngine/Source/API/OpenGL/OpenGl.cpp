#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Backend/WindowHandling.h"
#include <iostream>
#include "OpenGL.h"
#include "OpenGLRenderer.h"



namespace OpenGL {

	void Init() {
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to load GLAD\n";
			return;
		}
	}

	void InitRenderer() {
		OpenGLRenderer::Init();
	}

	void Render(int windowWidth, int windowHeight) {
		OpenGLRenderer::Render(windowWidth, windowHeight);
	}

	void Cleanup() {
		OpenGLRenderer::Cleanup();
	}

	void setViewport(void* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	void Clear() {
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	
}