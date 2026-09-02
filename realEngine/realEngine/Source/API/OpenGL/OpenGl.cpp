#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Backend/WindowHandling.h"
#include <iostream>
#include "OpenGL.h"
#include "OpenGLRenderer.h"



namespace OpenGL {

	float background_color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

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
		glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	
}