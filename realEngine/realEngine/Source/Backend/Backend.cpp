#include "Backend.h"
#include "WindowHandling.h"
#include "API/OpenGL/OpenGL.h"
#include "Input/Input.h"
#include "Camera/Camera.h"
#include <iostream>


namespace Backend {
	API g_api;
	WindowMode g_windowmode = WindowMode::WINDOWED;
	int g_windowWidth = 0;
	int g_windowHeight = 0;

	bool Init(API api, WindowMode windowmode) {
		g_api = api;
		g_windowmode = windowmode;
		if (!WindowHandling::Init(g_api, g_windowmode)) {
			std::cout << "WindowHandling Failed to Initialize\n";
			return false;
		}
		if (g_api == API::OpenGL) OpenGL::Init(); //Add an Else if (g_api == API::Vulkan) for Vulkan Integration.

		Camera::Init(glm::vec3(0,0,3)); // TEMP
		Input::Init(Backend::GetWindowPointer(), Camera::ProcessMouseMovement);

		//TEMP
		if (api == API::OpenGL) {
			OpenGL::InitRenderer();
		}


		g_windowWidth = WindowHandling::GetWindowWidth();
		g_windowHeight = WindowHandling::GetWindowHeight();

		return true;
	}

	void PreRender() {
		Input::Update();
	}

	void Render() {
		if (g_api == API::OpenGL) {
			OpenGL::Render(g_windowWidth, g_windowHeight);
		}
	}
	void PostRender() {
		WindowHandling::DisplayFrame();
		WindowHandling::PollEvents();
	}
	
	bool WindowIsOpen() {
		return WindowHandling::WindowIsOpen();
	}

	void* GetWindowPointer() {
		return WindowHandling::GetWindowPointer();
	}

	void Cleanup() {
		OpenGL::Cleanup();
		WindowHandling::Destroy();
	}

}