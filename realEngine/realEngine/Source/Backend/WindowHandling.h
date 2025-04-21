#pragma once
#include "Common/realEngineEnums.h"
#include <GLFW/glfw3.h>

namespace WindowHandling {
	bool Init(API api, WindowMode windowMode);
	GLFWwindow* GetWindowPointer();
	void Destroy();
	bool WindowIsOpen();
	bool SetWindowMode(WindowMode windowMode);
	void PollEvents();
	void DisplayFrame();
	void MakeContextCurrent();

	//Member Function - Remove from header and Find Alternate Solution ASAP
	//void m_framebuffer_size_callback(GLFWwindow* window, int width, int height);
}