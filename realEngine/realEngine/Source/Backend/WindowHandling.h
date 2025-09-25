#pragma once
#include "Common/realEngineEnums.h"

namespace WindowHandling {
	bool Init(API api, WindowMode windowMode);
	void* GetWindowPointer();
	void Destroy();
	bool WindowIsOpen();
	bool SetWindowMode(WindowMode windowMode);
	void PollEvents();
	void DisplayFrame();
	void MakeContextCurrent();
	int GetWindowWidth();
	int GetWindowHeight();
	void Close();

	//Member Function - Remove from header and Find Alternate Solution ASAP
	//void m_framebuffer_size_callback(GLFWwindow* window, int width, int height);
}