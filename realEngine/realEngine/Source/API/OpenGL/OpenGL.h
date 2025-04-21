#pragma once
#include <GLFW/glfw3.h>

namespace OpenGL {
	void Init();
	void Viewport(GLFWwindow* window, int width, int height);
	void Clear();	
}