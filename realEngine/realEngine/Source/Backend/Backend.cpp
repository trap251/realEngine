#include "Backend.h"
#include "WindowHandling.h"
#include "API/OpenGL/OpenGL.h"
#include "Input/Input.h"
#include <iostream>

namespace Backend {
	API g_api;
	WindowMode g_windowmode = WindowMode::WINDOWED;
	bool Init(API api, WindowMode windowmode) {
		g_api = api;
		g_windowmode = windowmode;
		if (!WindowHandling::Init(g_api, g_windowmode)) {
			std::cout << "WindowHandling Failed to Initialize\n";
			return false;
		}
		if (g_api == API::OpenGL) OpenGL::Init(); //Add an Else if (g_api == API::Vulkan) for Vulkan Integration.
		Input::Init(Backend::GetWindowPointer());
		return true;
	}

	void PreRender() {
		Input::Update();
	}

	void Render() {
		OpenGL::Clear();
	}
	void PostRender() {
		WindowHandling::DisplayFrame();
	}
	
	bool WindowIsOpen() {
		return WindowHandling::WindowIsOpen();
	}

	void* GetWindowPointer() {
		return WindowHandling::GetWindowPointer();
	}

	void Cleanup() {
		WindowHandling::Destroy();
	}

}