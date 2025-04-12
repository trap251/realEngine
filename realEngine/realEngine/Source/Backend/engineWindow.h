#pragma once
#include "../Common/realEngineEnums.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace engineWindow {
	bool Init(API api, WindowMode windowMode);
	GLFWwindow* GetWindow();
	void Kill();
	bool WindowIsOpen();
	void PollEvents();
	void DisplayFrame();
}